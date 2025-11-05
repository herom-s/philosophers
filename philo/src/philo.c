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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_philo	*create_philo(int philo_id)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_philo));
	new->philo_id = philo_id;
	gettimeofday(&new->time_last_eat, NULL);
	if (pthread_mutex_init(&new->philo_mutex, NULL) != 0)
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
	pthread_mutex_destroy(&p->philo_mutex);
	free(p);
}

int	create_philo_thread(t_philo *philo)
{
	return (pthread_create(&philo->philo_thread, NULL, philo_life,
			(void *)philo));
}

void	print_philo_msg(t_env *env, t_philo *philo, char *msg)
{
	char	*time_str;
	char	*philo_id_str;

	time_str = ft_itoa(get_elapsed_time(env->start_time));
	philo_id_str = ft_itoa(philo->philo_id + 1);
	pthread_mutex_lock(&env->print_mutex);
	write(1, time_str, ft_strlen(time_str));
	write(1, " ", 1);
	write(1, philo_id_str, ft_strlen(philo_id_str));
	write(1, " ", 1);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	pthread_mutex_unlock(&env->print_mutex);
	free(time_str);
	free(philo_id_str);
}
