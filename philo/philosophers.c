/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:28:51 by samartin          #+#    #+#             */
/*   Updated: 2023/12/12 13:53:34 by samartin         ###   ########.fr       */
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
	int	philos_done;
	int	be;

	be = 1;
	philos_done = 0;
	while (be && philos_done < god->n_philos)
	{
		if (god->n_philos == 1)
			usleep(500);
		else
			pthread_mutex_lock(&(god->table->own_fork->right_philo->sts_mtx));
		pthread_mutex_lock(&(god->table->sts_mtx));
		if (god->table->status == FED
			&& god->table->own_fork->right_philo->status == WAITING)
		{
			god->table->status = WAITING;
			god->table->own_fork->right_philo->status = READY;
		}
		pthread_mutex_unlock(&(god->table->sts_mtx));
		pthread_mutex_unlock(&(god->table->own_fork->right_philo->sts_mtx));
		god->table = god->table->own_fork->right_philo;
		pthread_mutex_lock(&(god->pdone_mtx));
		philos_done = god->philos_done;
		pthread_mutex_unlock(&(god->pdone_mtx));
		pthread_mutex_lock(&(god->be_mtx));
		be = god->be;
		pthread_mutex_unlock(&(god->be_mtx));
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
 * @return The main function returns 0 on uneventual exit.
 */
int	main(int argc, char **argv)
{
	t_god	*god;

	god = ph_parse(argc, argv);
	if (!god)
		return (-1);
	gettimeofday(&(god->the_beginning), NULL);
	god->be = 1;
	pthread_mutex_init(&(god->be_mtx), NULL);
	pthread_mutex_init(&(god->msg_mtx), NULL);
	pthread_mutex_init(&(god->pdone_mtx), NULL);
	while (god->table->id < god->n_philos)
	{
		ph_born(god->table);
		god->table = god->table->own_fork->right_philo;
	}
	ph_born(god->table);
	ph_cycle_of_life(god);
	ph_dinner_clean(god);
	return (0);
}
