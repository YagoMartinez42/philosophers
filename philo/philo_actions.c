#include "philosophers.h"

static void ph_live(t_philo philo) //¿Tenía que ser void???
{
	while (1) //check de muerte de hambre en cada acción con break
	{
		ph_think();
		ph_eat();
		ph_sleep();
	}
}

void	ph_born(t_philo	*philo)
{
	pthread_create(&(philo->own_being), NULL, ph_live, philo);
}