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
#include <sys/time.h>
#include <unistd.h>

void	philo_eat(t_env *env, t_philo *philo)
{
	if (philo_is_dead(env, philo))
		return ;
	philo->is_eating = 1;
	print_philo_msg(env, philo, "is eating");
	usleep(env->eat_time * 1000);
	gettimeofday(&philo->time_last_eat, NULL);
	philo->is_eating = 0;
	philo->eat_count++;
	if (philo_is_dead(env, philo))
		return ;
}

void	philo_think(t_env *env, t_philo *philo)
{
	if (philo_is_dead(env, philo))
		return ;
	philo->is_thinking = 1;
	print_philo_msg(env, philo, "is thinking");
	philo->is_thinking = 0;
	if (philo_is_dead(env, philo))
		return ;
}

void	philo_sleep(t_env *env, t_philo *philo)
{
	if (philo_is_dead(env, philo))
		return ;
	philo->is_sleeping = 1;
	print_philo_msg(env, philo, "is sleeping");
	usleep(env->sleep_time * 1000);
	philo->is_sleeping = 0;
	if (philo_is_dead(env, philo))
		return ;
}

int	philo_is_dead(t_env *env, t_philo *philo)
{
	if (get_elapsed_time(philo->time_last_eat) > env->death_time)
	{
		philo->is_dead = 1;
		return (1);
	}
	return (0);
}

#include <stdio.h>

void	*philo_life(void *arg)
{
	t_env	*env;
	t_philo	*philo;

	philo = (t_philo *)arg;
	env = philo->env;
	gettimeofday(&philo->time_last_eat, NULL);
	while (!philo_is_dead(env, philo))
	{
		while (!philo->has_left_fork)
		{
			if (ask_waiter_for_fork(philo->env, philo, LEFT_FORK) < 0)
				break ;
			else
			{
				print_philo_msg(env, philo, "has taken a fork");
				break ;
			}
		}
		while (!philo->has_right_fork)
		{
			if (ask_waiter_for_fork(philo->env, philo, RIGHT_FORK) < 0)
				break ;
			else
			{
				print_philo_msg(env, philo, "has taken a fork");
				break ;
			}
		}
		philo_eat(env, philo);
		give_waiter_fork(env, philo, LEFT_FORK);
		give_waiter_fork(env, philo, RIGHT_FORK);
		if (env->num_eat_times_philo > 0
			&& philo->eat_count >= env->num_eat_times_philo)
			break ;
		philo_sleep(env, philo);
		philo_think(env, philo);
	}
	if (philo->is_dead)
		print_philo_msg(env, philo, "died");
	return (NULL);
}
