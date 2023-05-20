/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:44:58 by samartin          #+#    #+#             */
/*   Updated: 2023/05/19 13:47:30 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(int code)
{
	if (code == 101)
	{
		printf ("Error: Wrong arguments\nShould be: philo ");
		printf ("number_of_philosophers time_to_die time_to_eat time_to_sleep");
		printf (" [number_of_times_each_philosopher_must_eat]\n");
	}
	else if (code == 102)
		printf("Error\nArgument not valid.\n", 2);
	else if (code == 105)
		code = 0;
	else
		ft_putstr_fd("Error\n(Untracked error)\n", 2);
	exit (code);
}
