/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:34:12 by hermarti          #+#    #+#             */
/*   Updated: 2025/11/03 19:27:40 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

void	set_env_vars(t_env *env, int argc, char *argv[])
{
	env->num_philos = ft_atoi(argv[1]);
	env->death_time = ft_atoi(argv[2]);
	env->eat_time = ft_atoi(argv[3]);
	env->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		env->num_eat_times_philo = ft_atoi(argv[5]);
}

int	set_env_philos(t_env *env)
{
	int	i;

	i = 0;
	env->philos = malloc(env->num_philos * sizeof(t_philo *));
	while (i < env->num_philos)
	{
		env->philos[i] = create_philo(i);
		if (env->philos[i] == NULL)
			return (-1);
		env->philos[i]->env = env;
		i++;
	}
	return (0);
}

int	set_env_forks(t_env *env)
{
	int	i;

	i = 0;
	env->forks = malloc(env->num_philos * sizeof(t_fork *));
	while (i < env->num_philos)
	{
		env->forks[i] = create_fork(i);
		if (env->forks[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

void	init_env(t_env *env, int argc, char *argv[])
{
	memset(env, 0, sizeof(t_env));
	gettimeofday(&env->start_time, NULL);
	if (pthread_mutex_init(&env->print_mutex, NULL) != 0)
		return ;
	set_env_vars(env, argc, argv);
	if (set_env_philos(env))
		print_error("Error: philos creation error");
	if (set_env_forks(env))
		print_error("Error: forks creation error");
}

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
		if (env->forks[i])
			free(env->forks[i]);
		i++;
	}
	free(env->forks);
}

void	clean_env(t_env *env)
{
	destroy_env_philos(env);
	destroy_env_forks(env);
	pthread_mutex_destroy(&env->print_mutex);
}
