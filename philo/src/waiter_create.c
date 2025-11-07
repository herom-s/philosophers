/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:33:35 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/07 20:34:09 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

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
