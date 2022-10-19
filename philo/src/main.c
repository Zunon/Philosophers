/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:19:15 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/19 06:53:16 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool numeric_args(int argc, char *argv[])
{
	int i;
	int j;
	
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("%c,\n", argv[i][j]);
				return (false);
			}
		}
	}
	return (true);
}

int	panic(char *msg, int errno)
{
	printf("ERROR: %s\n", msg);
	return (errno);
}

bool ul_overflow(unsigned long before, unsigned long after)
{
	return (((before >> 63) & 1) && !((after >> 63) & 1));
}

unsigned long	*atoul(const char *string, unsigned long *location)
{
	size_t			i;
	unsigned long	accumulator;
	unsigned long	temp;


	i = 0;
	accumulator = 0;
	while (string[i])
	{
		temp = accumulator;
		accumulator *= 10;
		accumulator += string[i++] + '0';
		if (ul_overflow(temp, accumulator))
			return (NULL);
	}
	*location = accumulator;
	return (location);
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
	{
		free(table->philosophers);
		table->philosophers = NULL;
		return (2);
	}
	while (++i < table->chairs)
	{
		table->forks[i] = (t_philo_fork){0};
		table->philosophers[i] = (t_philosopher){THINKING, &(table->forks[i]), &(table->forks[(i + 1) % table->chairs])};
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
	table->health = (t_philo_parameters){time_to_die, time_to_eat, time_to_sleep};
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

void	simulate_philosophers(t_roundtable *table)
{
	printf("World Simulated Successfully!\n");
	roundtable_destroy(table);
}

int main(int argc, char *argv[])
{
	t_roundtable	table;

	if (argc < 5 || argc > 6)
		return (panic("Incorrect Number of Arguments!", 1));
	else if (!numeric_args(argc, argv))
		return (panic("Non-Integer Arguments!", 2));
	else
	{
		if (argc > 5)
		{
			table.min_eats = malloc(sizeof(unsigned long));
			if (!(table.min_eats))
				return (panic("Couldn't Create Scenario!", 3));
		}
		else
			table.min_eats = NULL;
		if (roundtable_init(&table, argv + 1, argc > 5))
		{
			if (table.min_eats)
				free(table.min_eats);
			return (panic("Couldn't Create Scenario!", 3));
		}
		simulate_philosophers(&table);
		return (roundtable_destroy(&table));
	}
}
