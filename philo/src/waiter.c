/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:54:35 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/07 20:34:16 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

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

static int	check_philo_death(t_env *env, int i)
{
	int	elapsed;

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
			printf("%d %d died\n", elapsed, env->philos[i]->philo_id + 1);
		}
		pthread_mutex_unlock(&env->print_mutex);
		return (1);
	}
	return (0);
}

void	*waiter_check_philos(void *arg)
{
	t_env	*env;
	int		i;

	env = (t_env *)arg;
	while (should_continue_serving(env->waiter))
	{
		i = 0;
		while (i < env->num_philos)
		{
			if (check_philo_death(env, i))
				return (NULL);
			i++;
		}
		if (check_all_philos_done(env))
		{
			stop_serving(env->waiter);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
