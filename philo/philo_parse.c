/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:35:31 by samartin          #+#    #+#             */
/*   Updated: 2023/12/04 15:49:19 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_atoi(const char *str)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + *str - '0';
		str++;
	}
	nb = nb * sign;
	if (nb > __INT_MAX__)
		return (-1);
	else if (nb < (-(__INT_MAX__) - 1))
		return (0);
	else
		return ((int)nb);
}

static void	ph_close_the_circle(t_fork *last_fork, t_philo *first_philo)
{
	last_fork->right_philo = first_philo;
	first_philo->left_fork = last_fork;
}

static t_philo	*ph_put_the_table(t_god *god)
{
	t_philo	*first_philo_strt;
	t_philo	*philo_strt;
	t_fork	*last_fork;
	int		i;

	first_philo_strt = philo_new(1, god);
	last_fork = first_philo_strt->own_fork;
	i = 2;
	while (i <= god->n_philos)
	{
		philo_strt = philo_new(i, god);
		last_fork = philo_add(last_fork, philo_strt);
		if (!(i & 1))
			philo_strt->status = READY;
		i++;
	}
	if (i > 2)
		ph_close_the_circle(last_fork, first_philo_strt);
	return (first_philo_strt);
}

static int	ph_omnipotency(t_god *god)
{
	if (god->n_philos < 1 || god->time_2_die < 1 || god->time_2_eat < 1
		|| god->time_2_sleep < 1)
	{
		error_print (102);
		return (102);
	}
	god->table = ph_put_the_table(god);
	return (0);
}

t_god	*ph_parse(int argc, char **argv)
{
	t_god	*god;

	if (argc < 5 || argc > 6)
	{
		error_print(101);
		return (NULL);
	}
	god = malloc(sizeof(t_god));
	if (!god)
	{
		error_print(103);
		return (NULL);
	}
	memset(god, 0, sizeof(t_god));
	god->eat_cycles = -1;
	god->n_philos = ph_atoi(argv[1]);
	god->time_2_die = ph_atoi(argv[2]);
	god->time_2_eat = ph_atoi(argv[3]);
	god->time_2_sleep = ph_atoi(argv[4]);
	if (argc == 6)
		god->eat_cycles = ph_atoi(argv[5]);
	if (ph_omnipotency(god) > 0)
		return (NULL);
	return (god);
}
