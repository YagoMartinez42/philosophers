/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:28:51 by samartin          #+#    #+#             */
/*   Updated: 2023/07/13 18:56:11 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_leaks()
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_god	*god;

	atexit(check_leaks); //Ding Ding!!
	god = ph_parse(argc, argv);
	gettimeofday(&(god->the_beginning), NULL);
	god->be = 1;
	while (god->table->id != god->n_philos)
	{
		ph_born(god->table);
		god->table = god->table->own_fork->right_philo;
	}
	ph_born(god->table);
	while (god->be)
	{
		if (god->table->status == 2)
		{
			god->table->status = 0;
			god->table->own_fork->right_philo->status = 1;
		}
		god->table = god->table->own_fork->right_philo;
		usleep(10);
	}
	ph_dinner_clean(god);
	return (0);
}
