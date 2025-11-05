/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:36:49 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/28 15:36:52 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

t_fork	*create_fork(int fork_id)
{
	t_fork	*new;

	new = malloc(sizeof(t_fork));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_fork));
	new->fork_id = fork_id;
	if (pthread_mutex_init(&new->fork_mutex, NULL) != 0)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

void	*destroy_fork(t_fork *fork)
{
	if (!fork)
		return (NULL);
	pthread_mutex_destroy(&fork->fork_mutex);
	free(fork);
	return (NULL);
}
