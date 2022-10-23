/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:19:06 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/23 19:13:39 by kalmheir         ###   ########.fr       */
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

typedef enum e_philo_state
{
	BLANK,
	THINKING,
	EATING,
	SLEEPING,
	DEAD
}	t_philo_state;

typedef struct s_philo_fork
{
	pthread_mutex_t	mutex;
	bool			interest[2];
	bool			taken;
	t_direction		first;
}	t_philo_fork;

typedef struct s_philo_parameters
{
	t_milliseconds	starve_time;
	t_milliseconds	eat_time;
	t_milliseconds	sleep_time;
}	t_philo_parameters;

typedef struct s_philosopher
{
	pthread_t			soul;
	t_philo_fork		*left_fork;
	t_philo_fork		*right_fork;
	t_philo_parameters	*life;
	t_philo_state		current_state;
	bool				*reality;
}	t_philosopher;

typedef struct s_roundtable
{
	t_philo_fork		*forks;
	t_philosopher		*philosophers;
	t_philo_parameters	health;
	unsigned long		*min_eats;
	size_t				chairs;
	bool				sim_on;
}	t_roundtable;

bool			ul_overflow(unsigned long before, unsigned long after);
int				panic(char *msg, int errno);
bool			numeric_args(int argc, char *argv[]);
unsigned long	*atoul(const char *string, unsigned long *location);
int				roundtable_alloc(t_roundtable *table);
int				roundtable_init(t_roundtable *table, char *arguments[],
					bool eat_limit);
int				roundtable_destroy(t_roundtable *table);
void			simulate_philosophers(t_roundtable *table);
#endif
