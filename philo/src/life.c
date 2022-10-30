/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:30 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/30 14:22:32 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_reality(t_philosopher *oneself)
{
	bool	result;

	pthread_mutex_lock(&oneself->reality.mutex);
	result = oneself->reality.val;
	pthread_mutex_unlock(&oneself->reality.mutex);
	if (get_time_in_ms(oneself->begin) - oneself->last_eaten > oneself->life->starve_time)
		do_action(oneself, DEAD);
	return (result);
}

bool	check_turn(t_philosopher *me, t_philo_fork *low, t_philo_fork *high)
{
	bool	wait_turn;

	if (low == high)
		return (true);
	pthread_mutex_lock(&low->mutex);
	pthread_mutex_lock(&high->mutex);
	wait_turn = me->left_fork->first == LEFT || me->right_fork->first == RIGHT;
	if (wait_turn)
	{
		pthread_mutex_unlock(&high->mutex);
		pthread_mutex_unlock(&low->mutex);
	}
	return (wait_turn);
}

void	order_forks(t_philosopher *me, t_philo_fork *ord[2])
{
	if (me->left_fork < me->right_fork)
	{
		ord[0] = me->left_fork;
		ord[1] = me->right_fork;
	}
	else
	{
		ord[0] = me->right_fork;
		ord[1] = me->left_fork;
	}
}

void	*live_life(void *philo_data)
{
	t_philosopher	*my_data;
	bool			wait_turn;
	t_philo_fork	*ord[2];

	
	my_data = philo_data;
	wait_turn = true;
	order_forks(my_data, ord);
	while (check_reality(my_data))
	{
		while (wait_turn)
		{
			do_action(my_data, THINKING);
			if (!check_reality(my_data))
				return (NULL);
			wait_turn = check_turn(my_data, ord[0], ord[1]);
		}
		if (!check_reality(my_data))
		{
			pthread_mutex_unlock(&ord[0]->mutex);
			pthread_mutex_unlock(&ord[1]->mutex);
			return (NULL);
		}
		philo_eat(my_data, ord);
		if (!check_reality(my_data))
			return (NULL);
		do_action(my_data, SLEEPING);
		wait_turn = true;
	}
	return (NULL);
}

void	announce_action(t_philosopher *me, enum e_philo_state action)
{
	if (action == THINKING)
		printf("%zu %zu is thinking\n", get_time_in_ms(me->begin), me->name);
	else if (action == EATING)
		printf("%zu %zu is eating\n", get_time_in_ms(me->begin), me->name);
	else if (action == SLEEPING)
		printf("%zu %zu is sleeping\n", get_time_in_ms(me->begin), me->name);
	else if (action == DEAD)
		printf("%zu %zu died\n", get_time_in_ms(me->begin), me->name);
	else if (action == PICKING_UP_FORK)
		printf("%zu %zu has taken a fork\n%zu %zu has taken a fork\n", get_time_in_ms(me->begin), me->name, get_time_in_ms(me->begin), me->name);
}

void	do_action(t_philosopher *me, enum e_philo_state action)
{
	t_milliseconds			start;
	t_milliseconds			duration;

	pthread_mutex_lock(&me->current_state.mutex);
	if (me->current_state.state != action)
	{
		pthread_mutex_lock(&me->death_state->mutex);
		if (!me->death_state->val)
			announce_action(me, action);
		if (action == DEAD)
			me->death_state->val = true;
		pthread_mutex_unlock(&me->death_state->mutex);
		me->current_state.state = action;
		pthread_mutex_unlock(&me->current_state.mutex);
		if (action == EATING || action == SLEEPING)
		{
			start = get_time_in_ms(me->begin);
			if (action == EATING)
				duration = me->life->eat_time;
			else
				duration = me->life->sleep_time;
			while (get_time_in_ms(me->begin) - start < duration)
			{
				usleep(500);
				check_reality(me);
			}
		}
	}
	else
		pthread_mutex_unlock(&me->current_state.mutex);
}

void	philo_eat(t_philosopher *me, t_philo_fork *ord[2])
{
	ord[0]->taken = true;
	ord[1]->taken = true;
	pthread_mutex_unlock(&ord[1]->mutex);
	pthread_mutex_unlock(&ord[0]->mutex);
	do_action(me, PICKING_UP_FORK);
	me->last_eaten = get_time_in_ms(me->begin);
	do_action(me, EATING);
	pthread_mutex_lock(&ord[0]->mutex);
	pthread_mutex_lock(&ord[1]->mutex);
	ord[0]->taken = false;
	ord[1]->taken = false;
	me->left_fork->first = LEFT;
	me->right_fork->first = RIGHT;
	pthread_mutex_unlock(&ord[1]->mutex);
	pthread_mutex_unlock(&ord[0]->mutex);
	me->meals_eaten++;
	if (me->life->min_eats && me->meals_eaten == *me->life->min_eats)
	{
		pthread_mutex_lock(&me->done_eating.mutex);
		me->done_eating.val = true;
		pthread_mutex_unlock(&me->done_eating.mutex);
	}
}