/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:18:40 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/24 14:33:03 by kalmheir         ###   ########.fr       */
/*											                                  */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_simulation(t_roundtable *world)
{
	(void)world;
	// @TODO: CREATE THREADS
	// @TODO: DECIDE FORK PRIORITIES
	// @TODO: START MAIN LOOP
	return (0);
}

void	*live_life(void *philo_data)
{
	(void)philo_data;
	// @TODO: PETERSON'S SOLUTION ON EACH FORK
	// Busy Waiting = Think
	// When we lock both forks, Eat
	// When we finish eating, Sleep
	// @NOTE: Check reality between each action
	return (NULL);
}

void	philo_think(t_philosopher *oneself)
{
	(void)oneself;
}
