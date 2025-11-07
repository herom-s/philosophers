/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:29:47 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/07 20:30:07 by hermarti         ###   ########.fr       */
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
	philo->eat_count++;
	pthread_mutex_unlock(&philo->time_mutex);
	usleep(env->eat_time * 1000);
}

void	philo_think(t_env *env, t_philo *philo)
{
	int	time_to_think;

	print_philo_msg(env, philo, "is thinking");
	if (env->num_philos % 2 == 0)
		return ;
	time_to_think = (env->eat_time * 2) - env->sleep_time;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think > 0)
		usleep(time_to_think * 1000);
}

void	philo_sleep(t_env *env, t_philo *philo)
{
	print_philo_msg(env, philo, "is sleeping");
	usleep(env->sleep_time * 1000);
}
