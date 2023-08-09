/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:30:28 by samartin          #+#    #+#             */
/*   Updated: 2023/08/08 14:35:51 by samartin         ###   ########.fr       */
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
# define MOCK_MSG1 "says: You despicable being, you lured me into this trap!"
# define MOCK_MSG2 "says: Despite the rules from the gods above you tell that \
I should avoid dying! Twice is written!"
# define MOCK_MSG3 "says: You know what? I'm going to skip all your fucking \
universe rules and eat these spaguetti with my bare hands!"
# define MOCK_MSG4 "says: See? I don't need two forks to avoid starving while \
I'm in front of a plate full of food. Even more! You can take this fork I came \
with and stuck it in the place you like less!"
# define MOCK_MSG5 "died by some mysterious event, but not from starvation."
# define THINK_MSG "is thinking about life and the universe 🤔"
# define FORK_MSG "has taken a fork 🍴"
# define EAT_MSG "is eating 🍝"
# define SLEEP_MSG "is sleeping 😴"

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_god	t_god;
typedef struct timeval	t_timeval;

/**
 * Forks and philosophers make the same circular list connecting each philo with
 * two forks and each fork with two philos. No list is formed if there is only 1
 * @id: Each fork shares the same id as the philo "holding it with their
 *  right hand".
 * @philo: The left fork and philo to the right of the right (own) fork both
 *  start as NULL until set.
 */
typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mute_me;
	t_philo			*own_philo;
	t_philo			*right_philo;
}	t_fork;

/**
 * @id: Goes from 1 to the value of n_philos in the god.
 * @cycle: Count down from God's eat_cycle to zero.
 * @own_being: The thread that gives existence to the philo.
 * @status: 0 = waiting for turn to eat; 1 = ready to eat; 2 = eating;
 *  3 = finished eating, ready to pass the turn.
 * @last_meal: The time when last meal started or the thread was launched.
 * @own_fork: A pointer to the fork sharing their own id.
 * @var: left_fork A pointer to the fork of the previous philo. First philo will
 *  connect with the last fork when closing the circle.
 * @var: god A pointer to God, the central controller of the dinner.
 */
typedef struct s_philo
{
	int				id;
	int				cycle;
	pthread_t		own_being;
	size_t			status;
	t_timeval		last_meal;
	t_fork			*own_fork;
	t_fork			*left_fork;
	t_god			*god;
}	t_philo;

/**
 * God is the main controller of the dining philosophers.
 * @n_philos: Total amount of philos at the table. Set from param in main.
 * @time_2_die: Time in ms. If more than this time passes from the start of
 *  two meals, the philosopher dies from starvation.
 * @time_2_sleep: Time in ms that each philo passes sleeping after eating.
 * @eat_cycles: How many cycles are to be executed in the simulation if no
 *  philo dies before. If cycles param was not set, the flag is set to -1 and
 *  allows to run indefinitely.
 * @be: Existence flag. Turns to 1 when the philo threads start launching,
 *  and returns to 0 if one philo dies or all completed the amount of cycles.
 * @the_beginning: Timespamp to use as point zero reference.
 * @mute_msgs: A mutex to reserve the message posting.
 * @table: A pointer to the first philo and, as such, to the whole table.
 */
typedef struct s_god
{
	int				n_philos;
	int				time_2_die;
	int				time_2_eat;
	int				time_2_sleep;
	int				eat_cycles;
	int				philos_done;
	int				be;
	t_timeval		the_beginning;
	pthread_mutex_t	mute_msgs;
	t_philo			*table;
}	t_god;

void	error_exit(int code);
void	ph_dinner_clean(t_god *god);
t_god	*ph_parse(int argc, char **argv);
t_fork	*philo_add(t_fork *left_fork, t_philo *philo);
t_philo	*philo_new(size_t id, t_god *god);
void	ph_born(t_philo	*philo);
void	ph_msg(t_philo	*philo, char *msg);
long	ph_elapsed_micro(t_timeval beggining);
int		ph_are_you_ok(t_philo *philo);
void	*ph_mock(void *philo_arg);

#endif