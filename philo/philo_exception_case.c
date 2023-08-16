/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exception_case.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:54:43 by samartin          #+#    #+#             */
/*   Updated: 2023/08/16 15:45:00 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ph_mock(void *philo_arg)
{
	char	*msgs[5];
	int		i;
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->own_fork->right_philo = philo;
	msgs[0] = MOCK_MSG1;
	msgs[1] = MOCK_MSG2;
	msgs[2] = MOCK_MSG3;
	msgs[3] = MOCK_MSG4;
	msgs[4] = MOCK_MSG5;
	i = 0;
	while (i < 5)
	{
		ph_msg(philo, msgs[i]);
		usleep(philo->god->time_2_die * 250);
		i++;
	}
	philo->god->be = 0;
	return (NULL);
}
