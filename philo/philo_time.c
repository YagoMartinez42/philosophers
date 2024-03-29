/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:49:02 by samartin          #+#    #+#             */
/*   Updated: 2023/08/10 15:50:51 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_are_you_ok(t_philo *philo)
{
	if (ph_elapsed_micro(philo->last_meal) >= philo->god->time_2_die)
	{
		ph_msg(philo, DEATH_MSG);
		return (0);
	}
	return (1);
}

long	ph_elapsed_micro(t_timeval time_start)
{
	t_timeval	tnow;

	gettimeofday(&tnow, NULL);
	return ((tnow.tv_sec * 1000) + (tnow.tv_usec / 1000) - \
		((time_start.tv_sec) * 1000) - ((time_start.tv_usec) / 1000));
}
