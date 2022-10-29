/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:18:40 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/29 13:55:40 by kalmheir         ###   ########.fr       */
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

	i = -1;
	prioritize_forks(world->forks, world->chairs);
	while (++i < world->chairs)
		if (pthread_create(&(world->philosophers->soul), NULL, &live_life,
					(world->philosophers) + i))
			return (-1);
	world->sim_on = true;
	gettimeofday(&world->time, NULL);
	return (0);
}
