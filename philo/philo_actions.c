/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:57 by samartin          #+#    #+#             */
/*   Updated: 2023/07/21 16:53:17 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ph_think(t_philo *philo)
{
	printf("%li: Philosopher %i is thinking about life and the universe 🤔\n", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	while (philo->god->be && philo->status != 1)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (10);
	}
	return (0);
}

static int	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->own_fork->mute_me));
	printf("%li: Philosopher %i has taken a fork 🍴\n", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	pthread_mutex_lock(&(philo->left_fork->mute_me));
	printf("%li: Philosopher %i has taken a fork 🍴\n", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	gettimeofday(&(philo->last_meal), NULL);
	philo->status = 2;
	printf("%li: Philosopher %i is eating 🍝\n", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id);
	while (philo->god->be
		&& ph_elapsed_micro(philo->last_meal) < philo->god->time_2_eat)
	{
		if (!(ph_are_you_ok(philo)))
		{
			pthread_mutex_unlock(&(philo->own_fork->mute_me));
			pthread_mutex_unlock(&(philo->left_fork->mute_me));
			return (philo->id);
		}
		usleep (10);
	}
	pthread_mutex_unlock(&(philo->own_fork->mute_me));
	pthread_mutex_unlock(&(philo->left_fork->mute_me));
	philo->status = 3;
	if (philo->id == philo->god->n_philos)
		(philo->god->eat_cycles)--;
	return (0);
}

static int	ph_sleep(t_philo *philo)
{
	t_timeval	sleep_start;

	gettimeofday(&sleep_start, NULL);
	printf("%li: Philosopher %i is sleeping 😴\n", \
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
	while (philo->god->be)
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
	philo->last_meal.tv_sec = philo->god->the_beginning.tv_sec;
	philo->last_meal.tv_usec = philo->god->the_beginning.tv_usec;
	pthread_mutex_init(&(philo->own_fork->mute_me), NULL);
	if (philo->god->n_philos > 1)
		pthread_create(&(philo->own_being), NULL, ph_live, philo);
	else
		pthread_create (&(philo->own_being), NULL, ph_mock, philo);
}
