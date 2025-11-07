/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 18:12:29 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/03 18:34:07 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

void	philo_eat(t_env *env, t_philo *philo)
{
	print_philo_msg(env, philo, "is eating");
	pthread_mutex_lock(&philo->time_mutex);
	gettimeofday(&philo->time_last_eat, NULL);
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(env->eat_time * 1000);
	pthread_mutex_lock(&philo->time_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->time_mutex);
}

void	philo_think(t_env *env, t_philo *philo)
{
	int	time_to_think;

	print_philo_msg(env, philo, "is thinking");
	time_to_think = (env->death_time - env->eat_time - env->sleep_time) / 2;
	if (time_to_think > 0)
		usleep(time_to_think * 1000);
	else if (env->num_philos % 2 == 1)
		usleep(1000);
}

void	philo_sleep(t_env *env, t_philo *philo)
{
	print_philo_msg(env, philo, "is sleeping");
	usleep(env->sleep_time * 1000);
}

void	*philo_life(void *arg)
{
	t_env *env;
	t_philo *philo;
	int first_fork;
	int second_fork;
	int left_fork_id;
	int right_fork_id;

	philo = (t_philo *)arg;
	env = philo->env;
	pthread_mutex_lock(&philo->time_mutex);
	gettimeofday(&philo->time_last_eat, NULL);
	pthread_mutex_unlock(&philo->time_mutex);

	if (env->num_philos == 1)
	{
		print_philo_msg(env, philo, "has taken a fork");
		usleep(env->death_time * 1000);
		return (NULL);
	}

	left_fork_id = philo->philo_id;
	right_fork_id = (philo->philo_id + 1) % env->num_philos;

	if (left_fork_id < right_fork_id)
	{
		first_fork = LEFT_FORK;
		second_fork = RIGHT_FORK;
	}
	else
	{
		first_fork = RIGHT_FORK;
		second_fork = LEFT_FORK;
	}
	if (philo->philo_id % 2 == 1)
		usleep(env->eat_time * 500);

	while (!ask_waiter_someone_died(env))
	{
		if (ask_waiter_for_fork(env, philo, first_fork) < 0)
			break ;
		print_philo_msg(env, philo, "has taken a fork");

		if (ask_waiter_for_fork(env, philo, second_fork) < 0)
		{
			give_waiter_fork(env, philo, first_fork);
			break ;
		}
		print_philo_msg(env, philo, "has taken a fork");

		philo_eat(env, philo);
		give_waiter_fork(env, philo, first_fork);
		give_waiter_fork(env, philo, second_fork);

		pthread_mutex_lock(&philo->time_mutex);
		if (env->num_eat_times_philo > 0
			&& philo->eat_count >= env->num_eat_times_philo)
		{
			pthread_mutex_unlock(&philo->time_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->time_mutex);

		philo_sleep(env, philo);
		philo_think(env, philo);
	}
	return (NULL);
}