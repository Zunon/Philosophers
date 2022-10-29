/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:19:15 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/29 16:19:05 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	end_state_achieved(t_philosopher *philo, unsigned long *min_eats, size_t chairs)
{
	static unsigned long philos_done = 0;

	pthread_mutex_lock(&philo->current_state.mutex);
	if (philo->current_state.state == DEAD)
		return (true);
	if (min_eats)
	{
		if (philo->meals_eaten >= *min_eats)
			philos_done++;
		if (philos_done == chairs)
			return (true);
	}
	return (false);
}

void	end_simulation(t_roundtable *table)
{
	size_t i;

	table->sim_on = false;
	i = 0;
	while (i < table->chairs)
	{
		pthread_mutex_lock(&((table->philosophers + i)->reality.mutex));
		(table->philosophers + i)->reality.sim_on = false;
		pthread_mutex_unlock(&((table->philosophers + i)->reality.mutex));
		i++;
	}
}

void	dining_philos(t_roundtable *table)
{
	size_t i;

	i = 0;
	settimeofday(&table->time, NULL);
	while (i < table->chairs)
	{
		if (end_state_achieved(table->philosophers + i, table->min_eats,
					table->chairs))
		{
			end_simulation(table);
			break ;
		}
		i++;
	}
}

void	simulate_philosophers(t_roundtable *table)
{
	init_simulation(table);
	while (table->sim_on)
		dining_philos(table);
	printf("World Simulated!\n");
}

int	main(int argc, char *argv[])
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
