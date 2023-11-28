/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:44:58 by samartin          #+#    #+#             */
/*   Updated: 2023/11/28 16:36:51 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_print(int code)
{
	if (code == 101)
		write(2, ARGS_ERROR, 146);
	else if (code == 102)
		write(2, "Error\nArgument not valid.\n", 27);
	else if (code == 103)
		write(2, "Error\nUnable to allocate memory\n", 33);
	else
		write(2, "Error\n(Untracked error)\n", 33);
}

void	ph_dinner_clean(t_god *god)
{
	t_philo	*node;

	pthread_mutex_lock(&(god->be_mute));
	god->be = 0;
	pthread_mutex_unlock(&(god->be_mute));
	node = NULL;
	if (god->table && god->n_philos > 1)
		god->table->left_fork->right_philo = NULL;
	while (god->table)
	{
		if (god->n_philos > 1)
			node = god->table->own_fork->right_philo;
		if (god->table->status == 2)
		{
			pthread_mutex_unlock(&(god->table->own_fork->mute_me));
			pthread_mutex_unlock(&(god->table->left_fork->mute_me));
		}
		pthread_mutex_destroy(&(god->table->own_fork->mute_me));
		pthread_mutex_destroy(&(god->table->status_mute));
		pthread_detach(god->table->own_being);
		free(god->table->own_fork);
		free(god->table);
		god->table = node;
	}
	pthread_mutex_unlock(&(god->mute_msgs));
	pthread_mutex_destroy(&(god->be_mute));
	pthread_mutex_destroy(&(god->mute_msgs));
	pthread_mutex_destroy(&(god->pdone_mute));
	free(god);
}
