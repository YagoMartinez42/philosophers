/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:35:31 by samartin          #+#    #+#             */
/*   Updated: 2023/05/23 14:54:20 by samartin         ###   ########.fr       */
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

static int	ph_omnipotency(t_god *god)
{
	if (god->n_philos < 1)
		return (0);
	else if (god->time_2_die < 1)
		return (0);
	else if (god->time_2_eat < 1)
		return (0);
	else if (god->time_2_sleep < 1)
		return (0);
	return (1);
}

t_god	*ph_parse(int argc, char **argv)
{
	t_god	*god;

	if (argc < 5 || argc > 6)
		error_exit(101);
	god = malloc(sizeof(t_god));
	god->eat_cycles = -1;
	if (!god)
		error_exit (103);
	god->n_philos = ph_atoi(argv[1]);
	god->time_2_die = ph_atoi(argv[2]);
	god->time_2_eat = ph_atoi(argv[3]);
	god->time_2_sleep = ph_atoi(argv[4]);
	if (argc == 6)
		god->eat_cycles = ph_atoi(argv[5]);
	if (!(ph_omnipotency(god)))
		error_exit (102);
	return (god);
}
