/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:59:06 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/23 18:45:56 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_philosopher	philo_init(pthread_t soul, t_philo_state state,
		t_philo_fork *left, t_philo_fork *right)
{
	t_philosopher	result;

	result.soul = soul;
	result.current_state = state;
	result.left_fork = left;
	result.right_fork = right;
	return (result);
}

int	free_philos(t_philosopher **philo_arr)
{
	free(*philo_arr);
	*philo_arr = NULL;
	return (2);
}

int	roundtable_alloc(t_roundtable *table)
{
	size_t	i;

	i = -1;
	table->philosophers = malloc(table->chairs * sizeof(t_philosopher));
	if (!(table->philosophers))
		return (1);
	table->forks = malloc(table->chairs * sizeof(t_philo_fork));
	if (!(table->forks))
		return (free_philos(&table->philosophers));
	while (++i < table->chairs)
	{
		table->forks[i] = (t_philo_fork){0};
		table->philosophers[i] = philo_init(0, BLANK, &(table->forks[i]),
				&(table->forks[(i + 1) % table->chairs]));
		if (pthread_mutex_init(&(table->forks->mutex), NULL))
		{
			free(table->philosophers);
			free(table->forks);
			return (3);
		}
	}
	return (0);
}

int	roundtable_init(t_roundtable *table, char *arguments[], bool eat_limit)
{
	unsigned long	min_eats;
	size_t			number_of_philosophers;
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;

	if (!atoul(arguments[0], &number_of_philosophers) && number_of_philosophers)
		return (panic("Can't make that number of chairs!", 1));
	if (!atoul(arguments[1], &time_to_die))
		return (1);
	if (!atoul(arguments[2], &time_to_eat))
		return (1);
	if (!atoul(arguments[3], &time_to_sleep))
		return (1);
	if (eat_limit && !atoul(arguments[4], &min_eats))
		return (1);
	else if (eat_limit)
		*(table->min_eats) = min_eats;
	table->chairs = number_of_philosophers;
	table->health
		= (t_philo_parameters){time_to_die, time_to_eat, time_to_sleep};
	if (roundtable_alloc(table))
		return (2);
	return (0);
}

int	roundtable_destroy(t_roundtable *table)
{
	free(table->philosophers);
	free(table->forks);
	if (table->min_eats)
		free(table->min_eats);
	memset(table, 0x00, sizeof(t_roundtable));
	return (0);
}
