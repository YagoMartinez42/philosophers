/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:35:31 by samartin          #+#    #+#             */
/*   Updated: 2023/05/19 13:47:34 by samartin         ###   ########.fr       */
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

t_god	*ph_parse(t_god *god, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		error_exit(101);
	god = malloc(sizeof(t_god));
	if (!god)
		return (NULL);
	god->n_philos = ph_atoi(argv[1]);
	if (!(god->n_philos))
		error_exit(102);
	god->time_2_die = ph_atoi(argv[2]);
	if (!(god->time_2_die))
		error_exit(102);
	god->time_2_eat = ph_atoi(argv[3]);
	if (!(god->time_2_eat))
		error_exit(102);
	god->time_2_sleep = ph_atoi(argv[4]);
	if (!(god->time_2_sleep))
		error_exit(102);
	if (argc == 6)
	{
		god->eat_cycles = ph_atoi(argv[5]);
		if (!(god->eat_cycles))
			error_exit(102);
	}
	return (god);
}
