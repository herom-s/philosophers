/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:34:12 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/07 20:26:55 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>

void	destroy_env_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philos)
	{
		destroy_philo(env->philos[i]);
		i++;
	}
	free(env->philos);
}

void	destroy_env_forks(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philos)
	{
		destroy_fork(env->forks[i]);
		i++;
	}
	free(env->forks);
}

void	clean_env(t_env *env)
{
	destroy_env_philos(env);
	destroy_env_forks(env);
	destroy_waiter(env->waiter);
	pthread_mutex_destroy(&env->print_mutex);
}
