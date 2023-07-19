/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:30:28 by samartin          #+#    #+#             */
/*   Updated: 2023/07/19 17:18:27 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define ARGS_ERROR "Error: Wrong arguments\nShould be: philo \
number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_god	t_god;
typedef struct timeval	t_timeval;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mute_me;
	t_philo			*own_philo;
	t_philo			*right_philo;
}	t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	own_being;
	size_t		status;
	size_t		rest;
	t_timeval	last_meal;
	t_fork		*own_fork;
	t_fork		*left_fork;
	t_god		*god;
}	t_philo;

typedef struct s_god
{
	int			n_philos;
	int			time_2_die;
	int			time_2_eat;
	int			time_2_sleep;
	int			eat_cycles;
	int			be;
	t_timeval	the_beginning;
	t_philo		*table;
}	t_god;

void	error_exit(int code);
void	ph_dinner_clean(t_god *god);
t_god	*ph_parse(int argc, char **argv);
t_fork	*philo_add(t_fork *left_fork, t_philo *philo);
t_philo	*philo_new(size_t id, t_god *god);
void	ph_born(t_philo	*philo);
long	ph_elapsed_micro(t_timeval beggining);
int		ph_are_you_ok(t_philo *philo);

#endif