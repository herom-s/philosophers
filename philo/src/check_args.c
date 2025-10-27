/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:40:32 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/27 18:52:08 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_overflow_neg_zero(char *str_num)
{
	long	num;

	num = ft_atol(str_num);
	if (num < INT_MIN || num > INT_MAX)
		return (1);
	if (num <= 0)
		return (1);
	return (0);
}

int	check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (1);
	while (i < argc)
	{
		if (check_overflow_neg_zero(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
