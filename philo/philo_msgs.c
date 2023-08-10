/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 12:03:35 by samartin          #+#    #+#             */
/*   Updated: 2023/08/10 15:57:08 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&(philo->god->mute_msgs));
	if (philo->god->be)
		printf("%li: Philosopher %i %s\n", \
			ph_elapsed_micro(philo->god->the_beginning), philo->id, msg);
	if (*msg != 'D')
		pthread_mutex_unlock(&(philo->god->mute_msgs));
}
