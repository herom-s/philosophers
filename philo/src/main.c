/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:36:21 by hermarti          #+#    #+#             */
/*   Updated: 2025/10/27 18:58:52 by hermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (check_args(argc, argv))
		return (print_error("Error\n"));
	printf("Hello World\n");
	return (EXIT_SUCCESS);
}
