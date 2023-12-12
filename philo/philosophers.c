/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:28:51 by samartin          #+#    #+#             */
/*   Updated: 2023/12/12 15:13:57 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Checks the status of the philosopher's table and its right neighbor, and
 * updates their statuses if one just finished eating and the next was waiting.
 * There is an exception when there is only one philo, aplying a patch to give a
 * small pause to the outer loop that would be just going assigning the same
 * next philo as current at the table thousands of times per second.
 * 
 * @param god A pointer to a struct called "t_god" which contains information
 * about the philosophers and the table they are sitting at.
 */
static void	ph_pass_token_r(t_god *god)
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
}

/**
 * Manages the cycle of life for philosophers, passing the status token from one
 * to the next at their 'right' when they are done eating, allowing all them to
 * complete their cycles if a cycle value was set.
 * 
 * @param god A pointer to a structure of type "t_god", containing data about
 * the philosophers simulation and the dining table.
 */
static void	ph_cycle_of_life(t_god *god)
{
	int	philos_done;
	int	be;

	be = ph_get_sim_flag(god);
	philos_done = 0;
	while (be && philos_done < god->n_philos)
	{
		ph_pass_token_r(god);
		god->table = god->table->own_fork->right_philo;
		pthread_mutex_lock(&(god->pdone_mtx));
		philos_done = god->philos_done;
		pthread_mutex_unlock(&(god->pdone_mtx));
		be = ph_get_sim_flag(god);
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
