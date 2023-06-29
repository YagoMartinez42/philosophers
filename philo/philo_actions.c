/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:57 by samartin          #+#    #+#             */
/*   Updated: 2023/06/27 12:34:01 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void ph_think(t_philo *philo)
{
	philo = 0;
}

static void ph_eat(t_philo *philo)
{
	philo = 0;
}

static void ph_sleep(t_philo *philo)
{
	philo = 0;
}

static void	*ph_live(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (1) //check de muerte de hambre en cada acción con break
	{
		ph_think(philo);
		ph_eat(philo);
		ph_sleep(philo);
	}
	return (NULL);
}

void	ph_born(t_philo	*philo)
{
	pthread_create(&(philo->own_being), NULL, ph_live, philo);
}
