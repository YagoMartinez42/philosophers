/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:28:51 by samartin          #+#    #+#             */
/*   Updated: 2023/07/14 15:23:04 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/*
void	check_leaks()
{
	system("leaks -q philo");
}*/

int	main(int argc, char **argv)
{
	t_god	*god;

	//atexit(check_leaks); //Ding Ding!!
	god = ph_parse(argc, argv);
	gettimeofday(&(god->the_beginning), NULL);
	god->be = 1;
	printf ("existence is %i\n", god->be);
	printf ("y se hizo la luz en %li\n", god->the_beginning.tv_sec);
	while (god->table->id != god->n_philos)
	{
		printf ("philo %i\n", god->table->id);
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
