/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutexed_actions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:03:35 by samartin          #+#    #+#             */
/*   Updated: 2023/12/12 15:00:30 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_msg(t_philo *philo, char *msg)
{
	if (!philo || !msg)
		return ;
	pthread_mutex_lock(&(philo->god->msg_mtx));
	pthread_mutex_lock(&(philo->god->be_mtx));
	if (philo->god->be)
		printf("%li: Philosopher %i %s\n", \
			ph_elapsed_micro(philo->god->the_beginning), philo->id, msg);
	pthread_mutex_unlock(&(philo->god->be_mtx));
	pthread_mutex_unlock(&(philo->god->msg_mtx));
}

int	ph_get_sim_flag(t_god *god)
{
	int	be;

	pthread_mutex_lock(&(god->be_mtx));
	be = god->be;
	pthread_mutex_unlock(&(god->be_mtx));
	return (be);
}

void	ph_stop_sim(t_god *god)
{
	pthread_mutex_lock(&(god->be_mtx));
	god->be = 0;
	pthread_mutex_unlock(&(god->be_mtx));
}
