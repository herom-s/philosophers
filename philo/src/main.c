/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:36:21 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/03 19:28:52 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <sys/time.h>

int	main(int argc, char *argv[])
{
	int		i;
	t_env	env;

	if (check_args(argc, argv))
		return (print_error("Error\n"));
	init_env(&env, argc, argv);
	if (pthread_create(&env.waiter->waiter_thread, NULL, waiter_check_philos,
			&env) != 0)
	{
		clean_env(&env);
		return (print_error("Error: waiter thread creation failed\n"));
	}
	init_env_threads(&env);
	i = 0;
	while (i < env.num_philos)
		pthread_join(env.philos[i++]->philo_thread, NULL);
	pthread_join(env.waiter->waiter_thread, NULL);
	clean_env(&env);
	return (EXIT_SUCCESS);
}
