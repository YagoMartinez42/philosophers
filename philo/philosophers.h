/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:30:28 by samartin          #+#    #+#             */
/*   Updated: 2023/05/31 13:02:11 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define ARGS_ERROR "Error: Wrong arguments\nShould be: philo \
number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_fork
{
	size_t			id;
	pthread_mutex_t	mute_me;
	struct s_philo	*own_philo;
	struct s_philo	*right_philo;
}	t_fork;

typedef struct s_philo
{
	size_t			id;
	pthread_t		own_being;
	size_t			status;
	size_t			hunger;
	size_t			rest;
	struct s_fork	*own_fork;
	struct s_fork	*left_fork;
}	t_philo;

typedef struct s_god
{
	int				n_philos;
	int				time_2_die;
	int				time_2_eat;
	int				time_2_sleep;
	int				eat_cycles;
	struct s_philo	*table;
}	t_god;

void	error_exit(int code);
t_god	*ph_parse(int argc, char **argv);
t_fork	*philo_add(t_fork *left_fork, t_philo *philo);
t_philo	*philo_new(size_t id);

#endif