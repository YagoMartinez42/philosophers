/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samartin <samartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:30:28 by samartin          #+#    #+#             */
/*   Updated: 2023/12/12 13:53:32 by samartin         ###   ########.fr       */
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
# define THINK_MSG "is thinking about life and the universe 🤔"
# define FORK_MSG "has taken a fork 🍴"
# define EAT_MSG "is eating 🍝"
# define SLEEP_MSG "is sleeping 😴"
# define DEATH_MSG "DIED OF STARVATION 💀\n"
# define MOCK_MSG1 "says: You despicable being, you lured me into this trap!"
# define MOCK_MSG2 "says: Despite the rules from the gods above you tell that \
I should avoid dying! Twice is written!"
# define MOCK_MSG3 "says: You know what? I'm going to skip all your fucking \
universe rules and eat these spaguetti with my bare hands!"
# define MOCK_MSG4 "says: See? I don't need two forks to avoid starving while \
I'm in front of a plate full of food. Even more! You can take this fork I came \
with and stuck it in the place you like less!"
# define MOCK_MSG5 "died by some mysterious event, but not from starvation."

typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_god	t_god;
typedef struct timeval	t_timeval;
typedef enum e_status	t_status;

/**
 * Philosopher status enum
 */
enum e_status
{
	WAITING,
	READY,
	FEEDING,
	FED
};

/**
 * Forks and philosophers make the same circular list connecting each philo with
 * two forks and each fork with two philos. No list is formed if there is only 1
 * @id: Each fork shares the same id as the philo "holding it with their
 *  right hand".
 * @fork_itself: A flag representing the fork itself: 1 if the fork is in use.
 * @fk_mtx: The mutex to allow the philosopher reserve it.
 * @own_philo: A pointer to the philo sharing its own id. Can be considered
 *  being at the left off the fork.
 * @right_philo: The philo to the right, will start as NULL until set.
 */
struct s_fork
{
	int				id;
	int				fork_itself;
	pthread_mutex_t	fk_mtx;
	t_philo			*own_philo;
	t_philo			*right_philo;
};

/**
 * @id: Goes from 1 to the value of n_philos in the god.
 * @cycle: Count down from God's eat_cycle to zero.
 * @own_being: The thread that gives existence to the philo.
 * @status: Enumerated: 'WAITNG' (will stay thinking), 'READY' (will eat if it
 *  can take both forks), 'FEEDING', and 'FED' (ready to pass the turn).
 * @sts_mtx: The mutex to allow both the philo itself and God check and change
 *  the status.
 * @last_meal: The time when last meal started or the thread was launched.
 * @own_fork: A pointer to the fork sharing their own id.
 * @left_fork: A pointer to the fork of the previous philo. First philo will
 *  connect with the last fork when closing the circle.
 * @god: A pointer to God, the central controller of the dinner.
 */
struct s_philo
{
	int				id;
	int				cycle;
	pthread_t		own_being;
	t_status		status;
	pthread_mutex_t	sts_mtx;
	t_timeval		last_meal;
	t_fork			*own_fork;
	t_fork			*left_fork;
	t_god			*god;
};

/**
 * God is the main controller of the dining philosophers.
 * @n_philos: Total amount of philos at the table. Set from param in main.
 * @time_2_die: Time in ms. If more than this time passes from the start of
 *  two meals, the philosopher dies from starvation.
 * @time_2_eat: Time in ms that each philo takes to finish eating.
 * @time_2_sleep: Time in ms that each philo passes sleeping after eating.
 * @eat_cycles: How many cycles are to be executed in the simulation if no
 *  philo dies before. If cycles param was not set, the flag is set to -1 and
 *  allows to run indefinitely.
 * @be: Existence flag. Turns to 1 when the philo threads start launching,
 *  and returns to 0 if one philo dies or all completed the amount of cycles.
 * @the_beginning: Timespamp to use as point zero reference.
 * @msg_mtx: A mutex to reserve the message posting.
 * @table: A pointer to the first philo and, as such, to the whole table.
 */
struct s_god
{
	int				n_philos;
	int				time_2_die;
	int				time_2_eat;
	int				time_2_sleep;
	int				eat_cycles;
	int				philos_done;
	pthread_mutex_t	pdone_mtx;
	int				be;
	pthread_mutex_t	be_mtx;
	t_timeval		the_beginning;
	pthread_mutex_t	msg_mtx;
	t_philo			*table;
};

void	error_print(int code);
void	ph_dinner_clean(t_god *god);
t_god	*ph_parse(int argc, char **argv);
t_fork	*philo_add(t_fork *left_fork, t_philo *philo);
t_philo	*philo_new(size_t id, t_god *god);
void	ph_born(t_philo	*philo);
int		ph_think(t_philo *philo);
int		ph_eat(t_philo *philo);
int		ph_sleep(t_philo *philo);
void	ph_msg(t_philo	*philo, char *msg);
long	ph_elapsed_micro(t_timeval beggining);
int		ph_are_you_ok(t_philo *philo);

#endif