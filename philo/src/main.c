/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:19:15 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/31 16:09:55 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	end_simulation(t_roundtable *table)
{
	size_t	i;

	table->sim_on = false;
	i = 0;
	while (i < table->chairs)
	{
		pthread_mutex_lock(&((table->philosophers + i)->reality.mutex));
		(table->philosophers + i)->reality.val = false;
		pthread_mutex_unlock(&((table->philosophers + i)->reality.mutex));
		i++;
	}
	i = 0;
	while (i < table->chairs)
	{
		pthread_join((table->philosophers + i)->soul, NULL);
		i++;
	}
}

void	dining_philos(t_roundtable *table)
{
	size_t	i;
	bool	all_ate;

	i = 0;
	all_ate = true;
	pthread_mutex_lock(&table->death.mutex);
	if ((table->death.val && !pthread_mutex_unlock(&table->death.mutex))
		|| pthread_mutex_unlock(&table->death.mutex))
		return (end_simulation(table));
	while (i < table->chairs && table->health.min_eats)
	{
		usleep(250);
		pthread_mutex_lock(&(table->philosophers + i)->done_eating.mutex);
		if (!((table->philosophers + i)->done_eating.val))
		{
			pthread_mutex_unlock(&(table->philosophers + i)->done_eating.mutex);
			all_ate = false;
			break ;
		}
		pthread_mutex_unlock(&(table->philosophers + i++)->done_eating.mutex);
	}
	if (all_ate && table->health.min_eats)
		end_simulation(table);
}

void	simulate_philosophers(t_roundtable *table)
{
	if (init_simulation(table))
		printf("INITIALIZATION FAILURE\n");
	while (table->sim_on)
		dining_philos(table);
}

bool	can_announce(t_philosopher *me)
{
	bool	death_occured;
	bool	finished_eating;

	death_occured = me->death_state->val;
	if (me->life->min_eats)
		finished_eating = me->meals_eaten >= *me->life->min_eats;
	else
		finished_eating = false;
	return (!death_occured && !finished_eating);
}

/**
 * @brief main entry point of the program
 *
 * @param argc	amount of arguments that the program receives from the shell
 * @param argv	array of string arguments that the program received from the
 *				shell
 */
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
			table.health.min_eats = malloc(sizeof(unsigned long));
			if (!(table.health.min_eats))
				return (panic("Couldn't Create Scenario!", 3));
		}
		else
			table.health.min_eats = NULL;
		if (roundtable_init(&table, argv + 1, argc > 5))
		{
			if (table.health.min_eats)
				free(table.health.min_eats);
			return (panic("Couldn't Create Scenario!\n\
Make sure none of the arguments are zero or empty", 3));
		}
		simulate_philosophers(&table);
		return (roundtable_destroy(&table));
	}
}
