/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:44:58 by samartin          #+#    #+#             */
/*   Updated: 2023/08/10 15:56:31 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(int code)
{
	if (code == 101)
		printf(ARGS_ERROR);
	else if (code == 102)
		printf("Error\nArgument not valid.\n");
	else if (code == 103)
		printf("Error\nUnable to allocate memory\n");
	else
		printf("Error\n(Untracked error)\n");
	exit (code);
}

void	ph_dinner_clean(t_god *god)
{
	t_philo	*node;

	god->be = 0;
	node = NULL;
	if (god->table && god->n_philos > 1)
		god->table->left_fork->right_philo = NULL;
	pthread_mutex_unlock(&(god->mute_msgs));
	while (god->table)
	{
		if (god->n_philos > 1)
			node = god->table->own_fork->right_philo;
		pthread_join(god->table->own_being, NULL);
		if (god->table->status == 2)
		{
			pthread_mutex_unlock(&(god->table->own_fork->mute_me));
			pthread_mutex_unlock(&(god->table->left_fork->mute_me));
		}
		pthread_mutex_destroy(&(god->table->own_fork->mute_me));
		free(god->table->own_fork);
		free(god->table);
		god->table = node;
	}
	pthread_mutex_destroy(&(god->mute_msgs));
	free(god);
}
