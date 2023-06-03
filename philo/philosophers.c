/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:28:51 by samartin          #+#    #+#             */
/*   Updated: 2023/06/03 18:47:15 by samartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_leaks()
{
	system("leaks -q philo");
}

int	main(int argc, char **argv)
{
	t_god	*god;

	atexit(check_leaks);
	god = ph_parse(argc, argv);
	int i = 0;
	while (i < god->n_philos)
	{
		
		printf("%lu ", god->table->id);
		god->table = god->table->own_fork->right_philo;
		i++;
	}
	printf("And %lu again\n", god->table->id);
	ph_dinner_clean(god);
	return (0);
}
