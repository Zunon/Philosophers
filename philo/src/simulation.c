/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:18:40 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/28 17:25:02 by kalmheir         ###   ########.fr       */
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

	// @TODO: CREATE THREADS []
	// @TODO: DECIDE FORK PRIORITIES [x]
	// @TODO: START MAIN LOOP []
int	init_simulation(t_roundtable *world)
{
	prioritize_forks(world->forks, world->chairs);
	return (0);
}
