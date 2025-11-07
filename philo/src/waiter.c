/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:54:35 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/03 19:27:49 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_waiter	*create_waiter(void)
{
	t_waiter	*waiter;

	waiter = malloc(sizeof(t_waiter));
	if (!waiter)
		return (NULL);
	memset(waiter, 0, sizeof(t_waiter));
	waiter->continue_serving = 1;
	if (pthread_mutex_init(&waiter->any_death_check_mutex, NULL) != 0)
	{
		free(waiter);
		return (NULL);
	}
	if (pthread_mutex_init(&waiter->serving_check_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&waiter->any_death_check_mutex);
		free(waiter);
		return (NULL);
	}
	return (waiter);
}

void	*destroy_waiter(t_waiter *waiter)
{
	if (waiter)
	{
		pthread_mutex_destroy(&waiter->any_death_check_mutex);
		pthread_mutex_destroy(&waiter->serving_check_mutex);
		free(waiter);
		waiter = NULL;
	}
	return (NULL);
}

static int	get_fork_index(t_env *env, t_philo *philo, t_fork_type fork_type)
{
	if (fork_type == LEFT_FORK)
		return (philo->philo_id);
	return ((philo->philo_id + 1) % env->num_philos);
}

int	ask_waiter_for_fork(t_env *env, t_philo *philo, t_fork_type fork_type)
{
	int	fork_index;

	fork_index = get_fork_index(env, philo, fork_type);
	pthread_mutex_lock(&env->forks[fork_index]->fork_mutex);
	if (ask_waiter_someone_died(env))
	{
		pthread_mutex_unlock(&env->forks[fork_index]->fork_mutex);
		return (-1);
	}
	return (0);
}

void	give_waiter_fork(t_env *env, t_philo *philo, t_fork_type fork_type)
{
	int	fork_index;

	fork_index = get_fork_index(env, philo, fork_type);
	pthread_mutex_unlock(&env->forks[fork_index]->fork_mutex);
}

int	ask_waiter_someone_died(t_env *env)
{
	int	result;

	pthread_mutex_lock(&env->waiter->any_death_check_mutex);
	result = env->waiter->someone_died;
	pthread_mutex_unlock(&env->waiter->any_death_check_mutex);
	return (result);
}

int	check_all_philos_done(t_env *env)
{
	int	i;
	int	count;

	if (env->num_eat_times_philo <= 0)
		return (0);
	i = 0;
	count = 0;
	while (i < env->num_philos)
	{
		pthread_mutex_lock(&env->philos[i]->time_mutex);
		if (env->philos[i]->eat_count >= env->num_eat_times_philo)
			count++;
		pthread_mutex_unlock(&env->philos[i]->time_mutex);
		i++;
	}
	return (count == env->num_philos);
}

static int	should_continue_serving(t_waiter *waiter)
{
	int	result;

	pthread_mutex_lock(&waiter->serving_check_mutex);
	result = waiter->continue_serving;
	pthread_mutex_unlock(&waiter->serving_check_mutex);
	return (result);
}

static void	set_someone_died(t_waiter *waiter)
{
	pthread_mutex_lock(&waiter->any_death_check_mutex);
	waiter->someone_died = 1;
	pthread_mutex_unlock(&waiter->any_death_check_mutex);
}

static void	stop_serving(t_waiter *waiter)
{
	pthread_mutex_lock(&waiter->serving_check_mutex);
	waiter->continue_serving = 0;
	pthread_mutex_unlock(&waiter->serving_check_mutex);
}

void	*waiter_check_philos(void *arg)
{
	t_env *env = (t_env *)arg;
	int i;
	int elapsed;

	while (should_continue_serving(env->waiter))
	{
		i = 0;
		while (i < env->num_philos)
		{
			pthread_mutex_lock(&env->philos[i]->time_mutex);
			elapsed = get_elapsed_time(env->philos[i]->time_last_eat);
			pthread_mutex_unlock(&env->philos[i]->time_mutex);

			if (elapsed > env->death_time)
			{
				pthread_mutex_lock(&env->print_mutex);
				if (!ask_waiter_someone_died(env))
				{
					set_someone_died(env->waiter);
					stop_serving(env->waiter);
					elapsed = get_elapsed_time(env->start_time);
					printf("%d %d died\n", elapsed, env->philos[i]->philo_id
						+ 1);
				}
				pthread_mutex_unlock(&env->print_mutex);
				return (NULL);
			}
			i++;
		}
		if (check_all_philos_done(env))
		{
			stop_serving(env->waiter);
			return (NULL);
		}
	}
	return (NULL);
}
