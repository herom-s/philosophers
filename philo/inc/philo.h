/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 16:11:01 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/27 18:58:46 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_env
{
	int	num_philos;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	num_eat_times_philo;
}		t_env;

int		check_args(int argc, char *argv[]);
long	ft_atol(char *nptr);
int		ft_strlen(char *str);

int		print_error(char *erro_str);

#endif
