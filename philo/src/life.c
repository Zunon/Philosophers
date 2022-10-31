/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 17:25:30 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/31 16:06:18 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	check_reality(t_philosopher *oneself)
{
	bool	result;

	pthread_mutex_lock(&oneself->reality.mutex);
	result = oneself->reality.val;
	pthread_mutex_unlock(&oneself->reality.mutex);
	if (get_time_in_ms(oneself->begin) - oneself->last_eaten
		> oneself->life->starve_time)
		do_action(oneself, DEAD);
	usleep(10);
	return (result);
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
			return (unlock_both_forks(ord[0], ord[1]));
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
	int	red;
	int	green;
	int	blue;

	if (can_announce(me))
	{
		determine_colors(me, &red, &green, &blue);
		if (action == THINKING)
			printf("\033[38;2;%d;%d;%dm%zu %zu is thinking\033[0m\n", red, green,
				blue, get_time_in_ms(me->begin), me->name);
		else if (action == EATING)
			printf("\033[38;2;%d;%d;%dm%zu %zu is eating\033[0m\n", red, green,
				blue, get_time_in_ms(me->begin), me->name);
		else if (action == SLEEPING)
			printf("\033[38;2;%d;%d;%dm%zu %zu is sleeping\033[0m\n", red, green,
				blue, get_time_in_ms(me->begin), me->name);
		else if (action == DEAD)
			printf("\033[38;2;%d;%d;%dm%zu %zu died\033[0m\n", red, green, blue,
				get_time_in_ms(me->begin), me->name);
		else if (action == PICKING_UP_FORK)
			printf("\033[38;2;%d;%d;%dm%zu %zu has taken a fork\033[0m\n", red,
				green, blue, get_time_in_ms(me->begin), me->name);
		if (action == DEAD)
			me->death_state->val = true;
	}
}

void	do_action(t_philosopher *me, enum e_philo_state action)
{
	t_milliseconds			start;
	t_milliseconds			duration;

	pthread_mutex_lock(&me->current_state.mutex);
	if (me->current_state.state != action)
	{
		pthread_mutex_unlock(&me->current_state.mutex);
		pthread_mutex_lock(&me->death_state->mutex);
		announce_action(me, action);
		pthread_mutex_unlock(&me->death_state->mutex);
		if (action != PICKING_UP_FORK)
			change_state(me, action);
		if (action == EATING || action == SLEEPING)
		{
			start = get_time_in_ms(me->begin);
			if (action == EATING)
				duration = me->life->eat_time;
			else
				duration = me->life->sleep_time;
			while (get_time_in_ms(me->begin) - start < duration)
				check_reality(me);
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
	do_action(me, PICKING_UP_FORK);
	me->last_eaten = get_time_in_ms(me->begin);
	if (me->life->min_eats && me->meals_eaten == *me->life->min_eats)
	{
		pthread_mutex_lock(&me->done_eating.mutex);
		me->done_eating.val = true;
		pthread_mutex_unlock(&me->done_eating.mutex);
	}
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
}
