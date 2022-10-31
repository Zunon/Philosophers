/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:18:40 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/31 16:36:27 by kalmheir         ###   ########.fr       */
/*											                                  */
/* ************************************************************************** */

#include "../inc/philo.h"

void	change_state(t_philosopher *me, enum e_philo_state new_state)
{
	pthread_mutex_lock(&me->current_state.mutex);
	me->current_state.state = new_state;
	pthread_mutex_unlock(&me->current_state.mutex);
}

void	prioritize_forks(t_philo_fork *forks, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		(forks + i)->first = (t_direction)(1 + (i % 2));
		i++;
	}
}

int	roundtable_malloc_stuff(t_roundtable *table)
{
	if (pthread_mutex_init(&table->death.mutex, NULL))
		return (8);
	table->death.val = false;
	table->philosophers = malloc(table->chairs * sizeof(t_philosopher));
	if (!(table->philosophers))
		return (1);
	table->forks = malloc(table->chairs * sizeof(t_philo_fork));
	if (!(table->forks))
		return (free_philos(&table->philosophers));
	return (0);
}

int	init_simulation(t_roundtable *world)
{
	size_t		i;
	t_timeval	begin;

	prioritize_forks(world->forks, world->chairs);
	world->sim_on = true;
	gettimeofday(&begin, NULL);
	i = -1;
	while (++i < world->chairs)
	{
		world->philosophers[i].reality.val = true;
		world->philosophers[i].begin = begin;
	}
	i = -1;
	while (++i < world->chairs)
	{
		usleep(350);
		if (pthread_create(&((world->philosophers + i)->soul), NULL, &live_life,
				(world->philosophers) + i))
			return (-1);
	}
	return (0);
}
