/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:52:28 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/28 16:51:00 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atol(char *nptr)
{
	long	sign;
	long	n;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}

int	ft_atoi(char *nptr)
{
	return ((int)ft_atol(nptr));
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
