/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:34:26 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/07 20:35:22 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

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
