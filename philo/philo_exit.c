/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:44:58 by samartin          #+#    #+#             */
/*   Updated: 2023/07/13 18:55:46 by samartin         ###   ########.fr       */
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

	if (god->table)
		god->table->left_fork->right_philo = NULL;
	while (god->table)
	{
		node = god->table->own_fork->right_philo;
		pthread_join(god->table->own_being, NULL);
		free(god->table->own_fork);
		free(god->table);
		god->table = node;
	}
	free(god);
}
