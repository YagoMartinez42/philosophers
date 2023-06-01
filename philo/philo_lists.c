/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 14:05:08 by samartin          #+#    #+#             */
/*   Updated: 2023/05/31 13:16:52 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*philo_add(t_fork *left_fork, t_philo *philo)
{
	if (left_fork && philo)
	{
		left_fork->right_philo = philo;
		philo->left_fork = left_fork;
		return(philo->own_fork);
	}
	return (NULL);
}

t_philo	*philo_new(size_t id)
{
	t_philo	*philo_strt;
	t_fork	*fork_strt;

	philo_strt = (t_philo *)malloc(sizeof (t_philo));
	fork_strt = (t_fork *)malloc(sizeof (t_fork));
	if (!philo_strt || !fork_strt)
		return (NULL);
	memset(philo_strt, 0, sizeof(t_philo));
	memset(fork_strt, 0, sizeof(t_fork));
	philo_strt->id = id;
	fork_strt->id = id;
	philo_strt->own_fork = fork_strt;
	fork_strt->right_philo = NULL;
	return (philo_strt);
}