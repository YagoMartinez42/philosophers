/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:12:57 by samartin          #+#    #+#             */
/*   Updated: 2023/12/12 14:56:49 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ph_pickup_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->own_fork->fk_mtx));
	philo->own_fork->fork_itself = 1;
	ph_msg(philo, FORK_MSG);
	pthread_mutex_lock(&(philo->left_fork->fk_mtx));
	philo->left_fork->fork_itself = 1;
	ph_msg(philo, FORK_MSG);
	gettimeofday(&(philo->last_meal), NULL);
	pthread_mutex_lock(&(philo->sts_mtx));
	philo->status = FEEDING;
	pthread_mutex_unlock(&(philo->sts_mtx));
}

static void	ph_drop_forks(t_philo *philo)
{
	philo->own_fork->fork_itself = 0;
	pthread_mutex_unlock(&(philo->own_fork->fk_mtx));
	philo->left_fork->fork_itself = 0;
	pthread_mutex_unlock(&(philo->left_fork->fk_mtx));
	pthread_mutex_lock(&(philo->sts_mtx));
	philo->status = FED;
	pthread_mutex_unlock(&(philo->sts_mtx));
}

/**
 * A philosopher goes thinking only if there is no option to eat after sleeping,
 * thinking does not have a fixed duration, it goes until the philo's status
 * changes.
 * 
 * @return If the thinking loop is broken by status change, it will return 0. If
 * the function exit is due death (return of ph_are_you_ok is 0), it will return
 * the id of the perished philosopher.
 */
int	ph_think(t_philo *philo)
{
	int			be;
	t_status	status;

	be = ph_get_sim_flag(philo->god);
	ph_msg(philo, THINK_MSG);
	while (be && status != READY)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (200);
		be = ph_get_sim_flag(philo->god);
		pthread_mutex_lock(&(philo->sts_mtx));
		status = philo->status;
		pthread_mutex_unlock(&(philo->sts_mtx));
	}
	return (0);
}

/**
 * Makes a philosopher pick up two forks and start eating, looping during the
 * assigned eat time, then release the forks and set its status to FED. Still
 * checks for dying time, because if the parameter 'time_to_eat' is greater than
 * 'time_to_die', the specifications say they should die ('time_to_die' is to be
 * counted since the beginning of the last meal).
 * 
 * @return If the function is successful, it will return 0. But if the
 * 'ph_are_you ok' function returned 0 (they died), the return is the
 * philosopher's ID.
 */
int	ph_eat(t_philo *philo)
{
	int	be;

	ph_pickup_forks(philo);
	ph_msg(philo, EAT_MSG);
	be = ph_get_sim_flag(philo->god);
	while (be && ph_elapsed_micro(philo->last_meal) < philo->god->time_2_eat)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (200);
		be = ph_get_sim_flag(philo->god);
	}
	ph_drop_forks(philo);
	if (philo->cycle > 0)
	{
		philo->cycle--;
		if (!(philo->cycle))
		{
			pthread_mutex_lock(&(philo->god->pdone_mtx));
			philo->god->philos_done++;
			pthread_mutex_unlock(&(philo->god->pdone_mtx));
		}
	}
	return (0);
}

/**
 * Go sleep after eating. It takes the time stated in the launch parameters.
 * Still goes checking if the starving time catches the philosopher.
 * 
 * @return If the function is successful, it will return 0. But if the
 * 'ph_are_you ok' function returned 0 (they died), the return is the
 * philosopher's ID.
 */
int	ph_sleep(t_philo *philo)
{
	t_timeval	sleep_start;
	int			be;

	gettimeofday(&sleep_start, NULL);
	ph_msg(philo, SLEEP_MSG);
	be = ph_get_sim_flag(philo->god);
	while (be && ph_elapsed_micro(sleep_start) < philo->god->time_2_sleep)
	{
		if (!(ph_are_you_ok(philo)))
			return (philo->id);
		usleep (200);
		be = ph_get_sim_flag(philo->god);
	}
	return (0);
}
