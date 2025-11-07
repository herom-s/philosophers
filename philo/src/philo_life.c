/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:12:29 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/07 20:30:12 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

static void	init_philo_life(t_philo *philo, int *first, int *second)
{
	pthread_mutex_lock(&philo->time_mutex);
	gettimeofday(&philo->time_last_eat, NULL);
	pthread_mutex_unlock(&philo->time_mutex);
	if (philo->philo_id % 2 == 0)
	{
		*first = LEFT_FORK;
		*second = RIGHT_FORK;
	}
	else
	{
		*first = RIGHT_FORK;
		*second = LEFT_FORK;
	}
}

static int	handle_single_philo(t_env *env, t_philo *philo)
{
	print_philo_msg(env, philo, "has taken a fork");
	usleep(env->death_time * 1000);
	return (1);
}

static int	philo_eat_cycle(t_env *env, t_philo *philo, int first, int second)
{
	if (ask_waiter_for_fork(env, philo, first) < 0)
		return (0);
	print_philo_msg(env, philo, "has taken a fork");
	if (ask_waiter_for_fork(env, philo, second) < 0)
	{
		give_waiter_fork(env, philo, first);
		return (0);
	}
	print_philo_msg(env, philo, "has taken a fork");
	philo_eat(env, philo);
	give_waiter_fork(env, philo, first);
	give_waiter_fork(env, philo, second);
	pthread_mutex_lock(&philo->time_mutex);
	if (env->num_eat_times_philo > 0
		&& philo->eat_count >= env->num_eat_times_philo)
	{
		pthread_mutex_unlock(&philo->time_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->time_mutex);
	return (1);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	t_env	*env;
	int		first_fork;
	int		second_fork;

	philo = (t_philo *)arg;
	env = philo->env;
	init_philo_life(philo, &first_fork, &second_fork);
	if (env->num_philos == 1)
		return (handle_single_philo(env, philo), NULL);
	if (philo->philo_id % 2 == 1 && env->num_philos % 2 == 1)
		usleep(env->eat_time * 500);
	while (!ask_waiter_someone_died(env))
	{
		if (!philo_eat_cycle(env, philo, first_fork, second_fork))
			break ;
		philo_sleep(env, philo);
		philo_think(env, philo);
	}
	return (NULL);
}
