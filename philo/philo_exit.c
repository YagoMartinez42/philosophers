/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:44:58 by samartin          #+#    #+#             */
/*   Updated: 2023/12/12 13:53:50 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * Joins all the threads of the philosophers in the linked list, which is no
 * longer circular after setting to NULL the "next" value on one of the forks.
 * 
 * @param node A pointer to a struct representing a philosopher.
 */
static void	ph_join_all(t_philo *node)
{
	while (node)
	{
		pthread_join(node->own_being, NULL);
		node = node->own_fork->right_philo;
	}
}

/**
 * Clears all the resources used by the linked list of philosophers and forks.
 * 
 * @param node A pointer to the first philosopher in a linked list of
 * philosophers.
 */
static void	ph_clear_all(t_philo *node)
{
	t_philo	*aux;

	while (node)
	{
		aux = node->own_fork->right_philo;
		pthread_mutex_destroy(&(node->own_fork->fk_mtx));
		pthread_mutex_destroy(&(node->sts_mtx));
		free(node->own_fork);
		free(node);
		node = aux;
	}
}

/**
 * Preventively sets the 'be' flag to zero (under usual conditions should
 * already be zero) and cleans up the resources used during the dinner
 * simulation.
 * 
 * @param god A pointer to the controller struct that contained variables
 * and mutexes related to the general aspects of the simulation.
 */
void	ph_dinner_clean(t_god *god)
{
	pthread_mutex_lock(&(god->be_mtx));
	god->be = 0;
	pthread_mutex_unlock(&(god->be_mtx));
	pthread_mutex_unlock(&(god->msg_mtx));
	if (god->table && god->n_philos > 1)
		god->table->left_fork->right_philo = NULL;
	else
		god->table->own_fork->right_philo = NULL;
	ph_join_all(god->table);
	ph_clear_all(god->table);
	pthread_mutex_destroy(&(god->be_mtx));
	pthread_mutex_destroy(&(god->msg_mtx));
	pthread_mutex_destroy(&(god->pdone_mtx));
	free(god);
}

/**
 * Prints an error message on the stderror output based on the given error
 * code.
 * 
 * @param code An integer that represents the error code.
 */
void	error_print(int code)
{
	if (code == 101)
		write(2, ARGS_ERROR, 146);
	else if (code == 102)
		write(2, "Error: Argument not valid.\n", 28);
	else if (code == 103)
		write(2, "Error: Unable to allocate memory\n", 34);
	else
		write(2, "Error: (Untracked error)\n", 26);
}
