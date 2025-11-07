/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:26:33 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/07 20:26:48 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

void	init_env_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_philos)
	{
		create_philo_thread(env->philos[i]);
		i++;
	}
}
