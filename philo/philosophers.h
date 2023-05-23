/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:30:28 by samartin          #+#    #+#             */
/*   Updated: 2023/05/23 14:53:17 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# define ARGS_ERROR "Error: Wrong arguments\nShould be: philo \
number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_fork
{
	size_t			id;
	size_t			status;
	struct s_philo	*left;
	struct s_philo	*right;
}	t_fork;

typedef struct s_philo
{
	size_t			id;
	size_t			status;
	size_t			hunger;
	size_t			rest;
	struct s_fork	*left;
	struct s_fork	*right;
}	t_philo;

typedef struct s_god
{
	int	n_philos;
	int	time_2_die;
	int	time_2_eat;
	int	time_2_sleep;
	int	eat_cycles;
}	t_god;

void	error_exit(int code);
t_god	*ph_parse(int argc, char **argv);

#endif