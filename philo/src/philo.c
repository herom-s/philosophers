/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:37:20 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/03 19:27:30 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_philo	*create_philo(int philo_id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_philo));
	new->philo_id = philo_id;
	gettimeofday(&new->time_last_eat, NULL);
	if (pthread_mutex_init(&new->time_mutex, NULL) != 0)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

void	destroy_philo(void *philo)
{
	t_philo	*p;

	if (!philo)
		return ;
	p = (t_philo *)philo;
	pthread_mutex_destroy(&p->time_mutex);
	free(p);
}

int	create_philo_thread(t_philo *philo)
{
	return (pthread_create(&philo->philo_thread, NULL, philo_life,
			(void *)philo));
}

void	print_philo_msg(t_env *env, t_philo *philo, char *msg)
{
	int	elapsed;

	pthread_mutex_lock(&env->print_mutex);
	if (!ask_waiter_someone_died(env))
	{
		elapsed = get_elapsed_time(env->start_time);
		printf("%d %d %s\n", elapsed, philo->philo_id + 1, msg);
	}
	pthread_mutex_unlock(&env->print_mutex);
}
