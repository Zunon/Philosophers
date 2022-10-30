/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:18:40 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/30 13:40:32 by kalmheir         ###   ########.fr       */
/*											                                  */
/* ************************************************************************** */

#include "../inc/philo.h"

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

int	init_simulation(t_roundtable *world)
{
	size_t	i;
	t_timeval	begin;

	prioritize_forks(world->forks, world->chairs);
	world->sim_on = true;
	gettimeofday(&begin, NULL);
	i = -1;
	while (++i < world->chairs)
	{
		pthread_mutex_lock(&(world->philosophers[i].reality.mutex));
		world->philosophers[i].reality.val = true;
		world->philosophers[i].begin = begin;
		pthread_mutex_unlock(&(world->philosophers[i].reality.mutex));
	}
	i = -1;
	while (++i < world->chairs)
	{
		if (pthread_create(&((world->philosophers + i)->soul), NULL, &live_life,
					(world->philosophers) + i))
			return (-1);
	}
	return (0);
}
