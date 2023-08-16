/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:57 by samartin          #+#    #+#             */
/*   Updated: 2023/08/16 15:45:08 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * A philosopher goes thinking only if there is no option to eat after sleeping,
 * thinking does not have a fixed duration, it goes until the philo's status
 * changes.
 * 
 * @return If the thinking loop is broken by status change, it will return 0. If
 * the function exit is due death (return of ph_are_you_ok is 0), it will return
 * the id of the perished philo.
 */
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

/**
 * Makes a philosopher pick up two forks by muting them, looping during the
 * assigned eat time, then release the forks by unmuting and set their status
 * to '3' (done eating). Still checks for dying time, because if the parameter
 * 'time_to_eat' is greater than time_to_die, the specifications say they should
 * die (time_to_die is to be counted since the beginning of the last meal).
 * 
 * @return If the function is successful, it will return 0. But if the
 * 'ph_are_you ok' function returned 0 (they died), the return is the
 * philosopher's ID.
 */
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
 * @return If the function is successful, it will return 0. But if the
 * 'ph_are_you ok' function returned 0 (they died), the return is the
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
		pthread_create(&(philo->own_being), NULL, ph_mock, philo);
}
