/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:03:35 by samartin          #+#    #+#             */
/*   Updated: 2023/08/16 16:08:37 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_msg(t_philo *philo, char *msg)
{
	if (!philo || !msg)
		return ;
	pthread_mutex_lock(&(philo->god->mute_msgs));
	pthread_mutex_lock(&(philo->god->be_mute));
	if (philo->god->be)
		printf("%li: Philosopher %i %s\n", \
			ph_elapsed_micro(philo->god->the_beginning), philo->id, msg);
	pthread_mutex_unlock(&(philo->god->be_mute));
	if (*msg != 'D')
		pthread_mutex_unlock(&(philo->god->mute_msgs));
}
