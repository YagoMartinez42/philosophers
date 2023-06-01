/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:28:51 by samartin          #+#    #+#             */
/*   Updated: 2023/05/31 13:01:17 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_god	*god;

	god = ph_parse(argc, argv);
	printf ("num: %i, cycles: %i, die: %i, eat: %i, sleep: %i\n", god->n_philos, god->eat_cycles, god->time_2_die, god->time_2_eat, god->time_2_sleep);
	int i = 0;
	while (i < god->n_philos)
	{
		printf ("%lu ", god->table->id);
		god->table = god->table->left_fork->right_philo;
		i++;
	}
	printf ("And %lu again\n", god->table->id);
	return (0);
}
