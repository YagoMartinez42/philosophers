/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:57 by samartin          #+#    #+#             */
/*   Updated: 2023/08/10 16:08:43 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ph_think(t_philo *philo)
{
	ph_msg(philo, THINK_MSG);
	while (philo->god->be && philo->status != 1)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (200);
	}
	return (0);
}

static int	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->own_fork->mute_me));
	ph_msg(philo, FORK_MSG);
	pthread_mutex_lock(&(philo->left_fork->mute_me));
	ph_msg(philo, FORK_MSG);
	gettimeofday(&(philo->last_meal), NULL);
	philo->status = 2;
	ph_msg(philo, EAT_MSG);
	while (philo->god->be
		&& ph_elapsed_micro(philo->last_meal) < philo->god->time_2_eat)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (200);
	}
	pthread_mutex_unlock(&(philo->own_fork->mute_me));
	pthread_mutex_unlock(&(philo->left_fork->mute_me));
	philo->status = 3;
	if (philo->cycle > 0)
	{
		philo->cycle--;
		if (!(philo->cycle))
			philo->god->philos_done++;
	}
	return (0);
}

/**
 * Go sleep after eating. It takes the time stated in the launch parameters.
 * Still goes checking if the starving time catches the philo.
 * 
 * @param philo A pointer to a struct representing a philosopher.
 * 
 * @return an integer value. If the function is successful, it will return 0.
 * But if the 'ph_are_you ok' function returned 0 (they died), the return is the
 * philosopher's ID.
 */
static int	ph_sleep(t_philo *philo)
{
	t_timeval	sleep_start;

	gettimeofday(&sleep_start, NULL);
	ph_msg(philo, SLEEP_MSG);
	while (philo->god->be
		&& ph_elapsed_micro(sleep_start) < philo->god->time_2_sleep)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (200);
	}
	return (0);
}

/**
 * This is a thread function that represents the life cycle of a philo: Go think
 * in case it is not their turn to eat, eat once it is their turn, sleep once
 * finished eating. In each phase, if they find that the existence flag is
 * already just set to 0 or the return value of one of its steps is not 0 (so it
 * finished by dead), they end the loop.
 * 
 * @param philo_arg A void pointer that is cast to t_philo type.
 * 
 * @return Always NULL.
 */
static void	*ph_live(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	while (philo->god->be && philo->cycle)
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

/**
 * Initialize the fork mutex, set the last_meal time as the starting time,
 * and create a new thread for a philosopher. If there is only one philo,
 * start the mock exception.
 * 
 * @param philo A pointer to a struct representing a philosopher.
 */
void	ph_born(t_philo	*philo)
{
	pthread_mutex_init(&(philo->own_fork->mute_me), NULL);
	gettimeofday(&(philo->last_meal), NULL);
	if (philo->god->n_philos > 1)
		pthread_create(&(philo->own_being), NULL, ph_live, philo);
	else
	{
		philo->god->philos_done = 1;
		pthread_create (&(philo->own_being), NULL, ph_mock, philo);
	}
}
