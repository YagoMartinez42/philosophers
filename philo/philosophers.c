/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:28:51 by samartin          #+#    #+#             */
/*   Updated: 2023/08/17 11:23:19 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Manages the cycle of life for philosophers, passing the status token from one
 * to the next at their 'right' when they are done eating, allowing all them to
 * complete their cycles. There is an exception when there is only one philo,
 * aplying a patch to give a small pause to the loop that would be just asigning
 * the same philo to the current one being looked up at the table thousands of
 * times per second.
 * 
 * @param god A pointer to a structure of type "t_god", containing data about
 * the philosophers simulation and the dining table.
 */
static void	ph_cycle_of_life(t_god *god)
{
	while (god->be && god->philos_done < god->n_philos)
	{
		if (god->n_philos == 1)
			usleep(500);
		if (god->table->status == 3
			&& god->table->own_fork->right_philo->status == 0)
		{
			god->table->status = 0;
			god->table->own_fork->right_philo->status = 1;
		}
		god->table = god->table->own_fork->right_philo;
	}
	if (god->philos_done == god->n_philos)
		printf("%li: All %i philosophers completed their %i cycles\n", \
			ph_elapsed_micro(god->the_beginning), god->n_philos, \
			god->eat_cycles);
}

/**
 * This is a simuation of the dining philosophers. The main function calls in
 * order for the funcions that parse the arguments, initialize the 'god' data
 * structure and philos table and that create threads for each philosopher. Then
 * manages the lifecycle of the philosophers and ends the simulation joining the
 * threads and clearing the memory.
 * 
 * @param argc The number of command-line arguments passed to the program. It
 * includes the name of the program itself as the first argument.
 * @param argv An array of strings representing the command-line arguments
 * passed to the program.
 * 
 * @return The main function is returning 0.
 */
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
	ph_cycle_of_life(god);
	ph_dinner_clean(god);
	return (0);
}
