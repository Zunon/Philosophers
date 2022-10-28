/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:30 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/28 17:26:08 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

	// @TODO: PETERSON'S SOLUTION ON EACH FORK
	// Busy Waiting = Think
	// When we lock both forks, Eat
	// When we finish eating, Sleep
	// @NOTE: Check reality between each action
void	*live_life(void *philo_data)
{
	(void)philo_data;
	return (NULL);
}

void	philo_think(t_philosopher *oneself)
{
	(void)oneself;
}

void	philo_sleep(t_philosopher *oneself)
{
	(void)oneself;
}

void	philo_eat(t_philosopher *oneself)
{
	(void)oneself;
}
