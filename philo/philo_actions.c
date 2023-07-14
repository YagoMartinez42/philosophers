/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:57 by samartin          #+#    #+#             */
/*   Updated: 2023/07/14 15:20:33 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ph_think(t_philo *philo)
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

static int	ph_eat(t_philo *philo)
{
	printf("%li: Philosopher %i has taken a fork 🍴", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	printf("%li: Philosopher %i has taken a fork 🍴", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	gettimeofday(&(philo->last_meal), NULL);
	printf("%li: Philosopher %i is eating 🍝", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	while (philo->god->be
		&& ph_elapsed_micro(philo->last_meal) < philo->god->time_2_eat)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (10);
	}
	philo->status = 2;
	return (0);
}

static int	ph_sleep(t_philo *philo)
{
	t_timeval	sleep_start;

	gettimeofday(&sleep_start, NULL);
	printf("%li: Philosopher %i is sleeping 😴", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	while (philo->god->be
		&& ph_elapsed_micro(sleep_start) < philo->god->time_2_sleep)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (10);
	}
	return (0);
}

static void	*ph_live(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (1)
	{
		if (philo->status != 1)
		{
			if (!(philo->god->be) || ph_think(philo))
				philo->god->be = 0;
		}
		if (!(philo->god->be) || ph_eat(philo))
			philo->god->be = 0;
		if (!(philo->god->be) || ph_sleep(philo))
			philo->god->be = 0;
	}
	return (NULL);
}

void	ph_born(t_philo	*philo)
{
	printf ("existence is %i\n", philo->god->be);
	printf ("birth of Philo %d in %li\n", philo->id, philo->god->the_beginning.tv_sec);
	philo->last_meal.tv_sec = philo->god->the_beginning.tv_sec;
	philo->last_meal.tv_usec = philo->god->the_beginning.tv_usec;
	printf ("birth of Philo %d b \n", philo->id);
	pthread_create(&(philo->own_being), NULL, ph_live, philo);
}
