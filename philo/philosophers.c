/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:28:51 by samartin          #+#    #+#             */
/*   Updated: 2023/08/10 16:00:26 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_god	*god;

	god = ph_parse(argc, argv);
	gettimeofday(&(god->the_beginning), NULL);
	god->be = 1;
	pthread_mutex_init(&(god->mute_msgs), NULL);
	while (god->table->id != god->n_philos)
	{
		ph_born(god->table);
		god->table = god->table->own_fork->right_philo;
	}
	ph_born(god->table);
	while (god->be && god->philos_done < god->n_philos)
	{
		if (god->table->status == 3
			&& god->table->own_fork->right_philo->status == 0)
		{
			god->table->status = 0;
			god->table->own_fork->right_philo->status = 1;
		}
		god->table = god->table->own_fork->right_philo;
	}
	ph_dinner_clean(god);
	return (0);
}
