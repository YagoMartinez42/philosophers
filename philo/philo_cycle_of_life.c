/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle_of_life.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:40:30 by samartin          #+#    #+#             */
/*   Updated: 2023/12/12 12:38:24 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/**
 * This is a thread function that represents the life cycle of a philo: Go think
 * in case it is not its turn to eat, eat once it is its turn, sleep once
 * finished eating. In each phase, if it finds that the existence flag is
 * already just set to 0 or the return value of one of its steps is not 0 (so it
 * finished by dead), it ends the loop.
 * 
 * @param philo_arg A void pointer that is cast to t_philo type.
 * 
 * @return Always NULL.
 */
static void	*ph_live(void *philo_arg)
{
	t_philo		*philo;
	t_status	philo_status;
	int			be;

	philo = (t_philo *)philo_arg;
	pthread_mutex_lock(&(philo->god->be_mtx));
	be = philo->god->be;
	pthread_mutex_unlock(&(philo->god->be_mtx));
	while (be && philo->cycle)
	{
		pthread_mutex_lock(&(philo->sts_mtx));
		philo_status = philo->status;
		pthread_mutex_unlock(&(philo->sts_mtx));
		if (philo_status != READY)
		{
			if (ph_think(philo))
			{
				pthread_mutex_lock(&(philo->god->be_mtx));
				philo->god->be = 0;
				pthread_mutex_unlock(&(philo->god->be_mtx));
			}
		}
		if (ph_eat(philo))
		{
			pthread_mutex_lock(&(philo->god->be_mtx));
			philo->god->be = 0;
			pthread_mutex_unlock(&(philo->god->be_mtx));
		}
		if (!(philo->cycle))
			break ;
		if (ph_sleep(philo))
		{
			pthread_mutex_lock(&(philo->god->be_mtx));
			philo->god->be = 0;
			pthread_mutex_unlock(&(philo->god->be_mtx));
		}
		pthread_mutex_lock(&(philo->god->be_mtx));
		be = philo->god->be;
		pthread_mutex_unlock(&(philo->god->be_mtx));
	}
	return (NULL);
}

/**
 * Simulates the actions of a lone philosopher revelling against its fate by
 * printing messages spaced by a certain amount of time calculated from the
 * "time_2_die" value from the "god" struct. Sets the simulation flag to zero
 * after the performance.
 * 
 * @param philo_arg A pointer to a "t_philo" structure that supposedly will not
 * have any other philosopher along it in the list.
 * 
 * @return NULL.
 */
static void	*ph_mock(void *philo_arg)
{
	char	*msgs[5];
	int		i;
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	pthread_mutex_lock(&(philo->sts_mtx));
	philo->own_fork->right_philo = philo;
	pthread_mutex_unlock(&(philo->sts_mtx));
	msgs[0] = MOCK_MSG1;
	msgs[1] = MOCK_MSG2;
	msgs[2] = MOCK_MSG3;
	msgs[3] = MOCK_MSG4;
	msgs[4] = MOCK_MSG5;
	i = 0;
	while (i < 5)
	{
		ph_msg(philo, msgs[i]);
		usleep((philo->god->time_2_die * 250) - 800);
		i++;
	}
	pthread_mutex_lock(&(philo->god->be_mtx));
	philo->god->be = 0;
	pthread_mutex_unlock(&(philo->god->be_mtx));
	return (NULL);
}

/**
 * Initialize the fork and status mutexes, set the last_meal time as the
 * starting time, and create a new thread for a philosopher. If there is only
 * one philo, start the mock exception.
 * 
 * @param philo A pointer to a struct representing a philosopher.
 */
void	ph_born(t_philo	*philo)
{
	pthread_mutex_init(&(philo->own_fork->fk_mtx), NULL);
	pthread_mutex_init(&(philo->sts_mtx), NULL);
	gettimeofday(&(philo->last_meal), NULL);
	if (philo->god->n_philos > 1)
		pthread_create(&(philo->own_being), NULL, ph_live, philo);
	else
		pthread_create(&(philo->own_being), NULL, ph_mock, philo);
}
