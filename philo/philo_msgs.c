/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:03:35 by samartin          #+#    #+#             */
/*   Updated: 2023/12/12 13:53:36 by samartin         ###   ########.fr       */
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
