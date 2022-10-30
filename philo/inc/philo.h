/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:19:06 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/30 13:56:03 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>

typedef unsigned long	t_milliseconds;

typedef enum e_direction
{
	UNDECIDED,
	LEFT,
	RIGHT
}	t_direction;

enum e_philo_state
{
	BLANK,
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	PICKING_UP_FORK
};

typedef struct s_philo_state
{
	pthread_mutex_t	mutex;
	enum e_philo_state	state;
}	t_philo_state;

typedef struct s_bool_lock
{
	pthread_mutex_t mutex;
	bool			val;
}	t_bool_lock;

typedef struct s_meallock
{
	pthread_mutex_t mutex;
	unsigned long	meals;
}	t_meallock;

typedef struct timeval t_timeval;

typedef struct s_philo_fork
{
	pthread_mutex_t	mutex;
	bool			taken;
	t_direction		first;
}	t_philo_fork;

typedef struct s_philo_parameters
{
	t_milliseconds	starve_time;
	t_milliseconds	eat_time;
	t_milliseconds	sleep_time;
	unsigned long	*min_eats;
}	t_philo_parameters;

typedef struct s_philosopher
{
	pthread_t			soul;
	t_timeval			begin;
	size_t				name;
	t_milliseconds		last_eaten;
	t_bool_lock			done_eating;
	unsigned long		meals_eaten;
	t_philo_fork		*left_fork;
	t_philo_fork		*right_fork;
	t_philo_parameters	*life;
	t_philo_state		current_state;
	t_bool_lock			reality;
	t_bool_lock			*death_state;
}	t_philosopher;

typedef struct s_roundtable
{
	t_bool_lock			death;
	t_philo_fork		*forks;
	t_philosopher		*philosophers;
	t_philo_parameters	health;
	size_t				chairs;
	bool				sim_on;
}	t_roundtable;

int				init_simulation(t_roundtable *world);
bool			ul_overflow(unsigned long before, unsigned long after);
int				panic(char *msg, int errno);
bool			numeric_args(int argc, char *argv[]);
unsigned long	*atoul(const char *string, unsigned long *location);
int				roundtable_alloc(t_roundtable *table);
int				roundtable_init(t_roundtable *table, char *arguments[],
					bool eat_limit);
t_milliseconds	get_time_in_ms(t_timeval then);
void			*live_life(void *philo_data);
int				roundtable_destroy(t_roundtable *table);
void			simulate_philosophers(t_roundtable *table);
void			philo_think(t_philosopher *oneself);
void			philo_eat(t_philosopher *me, t_philo_fork *ord[2]);
t_milliseconds	get_time_in_ms(t_timeval then);
void			do_action(t_philosopher *me, enum e_philo_state action);
#endif
