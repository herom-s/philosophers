/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:10:44 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/29 14:45:09 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <bits/types/struct_timeval.h>
#include <stdlib.h>
#include <sys/time.h>

static size_t	ft_count_digits(int n)
{
	size_t		count_d;
	long int	nb;

	nb = n;
	count_d = 0;
	if (nb < 0)
	{
		count_d++;
		nb *= -1;
	}
	while (nb >= 10)
	{
		nb /= 10;
		count_d++;
	}
	count_d++;
	return (count_d);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		len;
	long int	nb;
	size_t		i;

	len = ft_count_digits(n);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return ((void *)0);
	nb = n;
	i = len - 1;
	if (nb < 0)
	{
		nb *= -1;
		res[0] = '-';
	}
	while (nb >= 10)
	{
		res[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	res[i] = nb + '0';
	res[len] = '\0';
	return (res);
}

int	get_elapsed_time(struct timeval start_time)
{
	struct timeval	current_time;
	int				elapsed;

	gettimeofday(&current_time, NULL);
	elapsed = (current_time.tv_sec - start_time.tv_sec) * 1000;
	elapsed += (current_time.tv_usec - start_time.tv_usec) / 1000;
	return (elapsed);
}
