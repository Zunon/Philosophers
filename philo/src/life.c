/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:30 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/29 22:58:36 by kalmheir         ###   ########.fr       */
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
	t_philosopher	*my_data;
	bool			wait_turn;
	t_philo_fork	*low;
	t_philo_fork	*high;

	my_data = philo_data;
	wait_turn = true;
	if (my_data->left_fork < my_data->right_fork)
	{
		low = my_data->left_fork;
		high = my_data->right_fork;
	}
	else
	{
		low = my_data->right_fork;
		high = my_data->left_fork;
	}
	while (wait_turn)
	{
		philo_think(my_data);
		check_reality(my_data);
		pthread_mutex_lock(&low->mutex);
		pthread_mutex_lock(&high->mutex);
		wait_turn = my_data->left_fork->first == LEFT || my_data->right_fork->first == RIGHT;
		pthread_mutex_unlock(&high->mutex);
		pthread_mutex_unlock(&low->mutex);
	}
	printf("Locking left! %zu\n", my_data->name);
	pthread_mutex_lock(&low->mutex);
	low->taken = true;
	printf("Locking right! %zu\n", my_data->name);
	pthread_mutex_lock(&high->mutex);
	high->taken = true;
	printf("Eating! %zu\n", my_data->name);
	low->taken = false;
	high->taken = false;
	my_data->left_fork->first = LEFT;
	my_data->right_fork->first = RIGHT;
	pthread_mutex_unlock(&high->mutex);
	printf("Unlocking right! %zu\n", my_data->name);
	pthread_mutex_unlock(&low->mutex);
	printf("Unlocking left! %zu\n", my_data->name);
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
