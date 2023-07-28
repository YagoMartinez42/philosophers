/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exception_case.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:54:43 by samartin          #+#    #+#             */
/*   Updated: 2023/07/21 18:08:04 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	pos;

	if (dest && src)
	{
		pos = -1;
		while (src[++pos] != 0)
			dest[pos] = src[pos];
		dest[pos] = src[pos];
	}
	return (dest);
}

void	*ph_mock(void *philo_arg)
{
	char	msgs[5][200];
	int		i;
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->own_fork->right_philo = philo;
	ft_strcpy (msgs[0], MOCK_MSG1);
	ft_strcpy (msgs[1], MOCK_MSG2);
	ft_strcpy (msgs[2], MOCK_MSG3);
	ft_strcpy (msgs[3], MOCK_MSG4);
	ft_strcpy (msgs[4], MOCK_MSG5);
	i = 0;
	while (i < 5)
	{
		printf("%li: Philosopher %i %s\n", \
		ph_elapsed_micro(philo->god->the_beginning), philo->id, msgs [i]);
		usleep(philo->god->time_2_die * 250);
		i++;
	}
	philo->god->be = 0;
	return (NULL);
}
