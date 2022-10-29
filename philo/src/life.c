/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:30 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/29 20:05:11 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	check_reality(t_philosopher *oneself)
{
	(void)oneself;
}

	// @TODO: PETERSON'S SOLUTION ON EACH FORK
	// Busy Waiting = Think
	// When we lock both forks, Eat
	// When we finish eating, Sleep
	// @NOTE: Check reality between each action
void	*live_life(void *philo_data)
{
	t_philosopher *my_data;

	my_data = philo_data;
	my_data->left_fork->interest[1] = true;
	my_data->right_fork->interest[0] = true;
	while (my_data->left_fork->interest[0] && my_data->left_fork->first == LEFT)
	{
		philo_think(my_data);
		check_reality(my_data);
	}
	pthread_mutex_lock(&my_data->current_state.mutex);
	my_data->current_state.state = DEAD;
	pthread_mutex_unlock(&my_data->current_state.mutex);
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
