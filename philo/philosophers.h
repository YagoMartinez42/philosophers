/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:30:28 by samartin          #+#    #+#             */
/*   Updated: 2023/05/19 13:00:55 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

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
	size_t			n_philos;
	size_t			time_2_die;
	size_t			time_2_eat;
	size_t			time_2_sleep;
	size_t			eat_cycles;
}	t_god;

void	error_exit(int code);

#endif