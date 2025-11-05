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
#include <unistd.h>

int	ask_waiter_for_fork(t_env *env, t_philo *philo, t_fork_type fork_type)
{
	int	fork_index;

	if (philo_is_dead(env, philo))
		return (-1);
	if (fork_type == LEFT_FORK)
		fork_index = philo->philo_id;
	else
		fork_index = (philo->philo_id + 1) % env->num_philos;
	if (!env->forks[fork_index]->is_taken)
	{
		env->forks[fork_index]->is_taken = 1;
		if (fork_type == LEFT_FORK)
			philo->has_left_fork = 1;
		else if (fork_type == RIGHT_FORK)
			philo->has_right_fork = 1;
	}
	pthread_mutex_lock(&env->forks[fork_index]->fork_mutex);
	return (0);
}

void	give_waiter_fork(t_env *env, t_philo *philo, t_fork_type fork_type)
{
	int	fork_index;

	if (fork_type == LEFT_FORK)
		fork_index = philo->philo_id;
	else
		fork_index = (philo->philo_id + 1) % env->num_philos;
	env->forks[fork_index]->is_taken = 0;
	if (fork_type == LEFT_FORK)
		philo->has_left_fork = 0;
	else if (fork_type == RIGHT_FORK)
		philo->has_right_fork = 0;
	pthread_mutex_unlock(&env->forks[fork_index]->fork_mutex);
}
