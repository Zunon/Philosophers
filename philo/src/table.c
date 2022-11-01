/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:59:06 by kalmheir          #+#    #+#             */
/*   Updated: 2022/11/01 11:54:51 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philosopher	philo_init(t_roundtable *world, size_t name,
		t_philo_fork *pair[2])
{
	t_philosopher	result;

	result.soul = 0;
	pthread_mutex_init(&result.current_state.mutex, NULL);
	result.current_state.state = BLANK;
	result.name = name + 1;
	result.left_fork = pair[0];
	result.right_fork = pair[1];
	pthread_mutex_init(&result.reality.mutex, NULL);
	result.reality.val = false;
	result.life = &(world->health);
	pthread_mutex_init(&result.done_eating.mutex, NULL);
	result.done_eating.val = 0;
	result.meals_eaten = 0;
	result.last_eaten = 0;
	result.death_state = &world->death;
	result.hue = ((float)result.name - 1) / ((float)(world->chairs));
	return (result);
}

int	free_philos(t_philosopher **philo_arr)
{
	free(*philo_arr);
	*philo_arr = NULL;
	return (2);
}

/**
 * @brief	allocate everything that needs to be dynamically allocated for the
 *			simulation
 */
int	roundtable_alloc(t_roundtable *table)
{
	size_t			i;
	t_philo_fork	*reach[2];

	i = -1;
	if (roundtable_malloc_stuff(table))
		return (1);
	while (++i < table->chairs)
	{
		reach[0] = &(table->forks[i]);
		reach[1] = &(table->forks[(i + 1) % table->chairs]);
		table->forks[i] = (t_philo_fork){0};
		table->philosophers[i] = philo_init(table, i, reach);
		if (pthread_mutex_init(&((table->forks + i)->mutex), NULL))
		{
			free(table->philosophers);
			free(table->forks);
			return (3);
		}
	}
	return (0);
}

/**
 * @brief	initialize our program variables (the world/table struct)
 *
 * @param table		pointer to where our program variables are stored
 * @param arguments	array of numeric strings to be used to set simulation
 *					parameters
 * @param eat_limit	whether or not we have an eating minimum supplied to our
 *					program
 */
int	roundtable_init(t_roundtable *table, char *arguments[], bool eat_limit)
{
	unsigned long	min_eats;
	size_t			number_of_philosophers;
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;

	if (!atoul(arguments[0], &number_of_philosophers))
		return (panic("Can't make that number of chairs!", 1));
	if (!atoul(arguments[1], &time_to_die))
		return (1);
	if (!atoul(arguments[2], &time_to_eat))
		return (1);
	if (!atoul(arguments[3], &time_to_sleep))
		return (1);
	table->health
		= (t_philo_parameters){time_to_die, time_to_eat, time_to_sleep,
		table->health.min_eats};
	if (eat_limit && !atoul(arguments[4], &min_eats))
		return (1);
	else if (eat_limit)
		*(table->health.min_eats) = min_eats;
	table->chairs = number_of_philosophers;
	if (roundtable_alloc(table))
		return (2);
	return (0);
}

int	roundtable_destroy(t_roundtable *table)
{
	size_t	i;

	i = -1;
	while (++i < table->chairs)
	{
		pthread_mutex_destroy(&((table->forks)[i].mutex));
		pthread_mutex_destroy(&((table->philosophers)[i].current_state.mutex));
		pthread_mutex_destroy(&((table->philosophers)[i].reality.mutex));
		pthread_mutex_destroy(&((table->philosophers)[i].done_eating.mutex));
	}
	free(table->philosophers);
	free(table->forks);
	if (table->health.min_eats)
		free(table->health.min_eats);
	memset(table, 0x00, sizeof(t_roundtable));
	return (0);
}
