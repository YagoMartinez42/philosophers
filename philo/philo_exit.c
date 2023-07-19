/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:44:58 by samartin          #+#    #+#             */
/*   Updated: 2023/07/19 17:29:58 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_exit(int code)
{
	if (code == 101)
		perror(ARGS_ERROR);
	else if (code == 102)
		perror("Error\nArgument not valid.\n");
	else if (code == 103)
		perror("Error\nUnable to allocate memory\n");
	else
		perror("Error\n(Untracked error)\n");
	exit (code);
}

void	ph_dinner_clean(t_god *god)
{
	t_philo	*node;

	god->be = 0;
	if (god->table)
		god->table->left_fork->right_philo = NULL;
	while (god->table)
	{
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
	free(god);
}
