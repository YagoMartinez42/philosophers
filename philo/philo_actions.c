/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:57 by samartin          #+#    #+#             */
/*   Updated: 2023/07/06 18:24:30 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int ph_think(t_philo *philo)
{
	printf("%li: Philosopher %i is thinking about life and the universe 🤔", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	while (philo->status != 1)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (10);
	}
	return (0);
}

static int ph_eat(t_philo *philo)
{
	printf("%li: Philosopher %i has taken a fork 🍴", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	printf("%li: Philosopher %i has taken a fork 🍴", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	printf("%li: Philosopher %i is eating 🍝", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	//while (1)

}

static int ph_sleep(t_philo *philo)
{
	printf("%li: Philosopher %i is sleeping 😴", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);

}

static void	*ph_live(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		if (ph_think(philo))
			ph_dinner_clean(philo->god, philo->id);
		if (ph_eat(philo))
			ph_dinner_clean(philo->god, philo->id);
		if (ph_sleep(philo))
			ph_dinner_clean(philo->god, philo->id);
	}
	return (NULL);
}

void	ph_born(t_philo	*philo)
{
	philo->last_meal = philo->god->the_beginning;
	pthread_create(&(philo->own_being), NULL, ph_live, philo);
}
