/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:53:27 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/31 12:53:24 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_milliseconds	get_time_in_ms(t_timeval then)
{
	t_timeval			now;

	gettimeofday(&now, NULL);
	return (1000 * (now.tv_sec - then.tv_sec)
		+ (now.tv_usec - then.tv_usec) / 1000);
}

void	*unlock_both_forks(t_philo_fork *low, t_philo_fork *high)
{
	pthread_mutex_unlock(&high->mutex);
	pthread_mutex_unlock(&low->mutex);
	return (NULL);
}

void	determine_colors(t_philosopher *me, int *red, int *green, int *blue)
{
	int	minimum;

	*red = 255.0 - (me->hue * 255.0);
	*green = (me->hue * 510.0);
	*blue = (me->hue * 255.0);
	if (*green > 255)
		*green = 510 - *green;
	minimum = *red;
	if (*green < minimum)
		minimum = *green;
	if (*blue < minimum)
		minimum = *blue;
	if (minimum < 150)
	{
		*red += 150 - minimum;
		*green += 150 - minimum;
		*blue += 150 - minimum;
	}
	if (*red > 255)
		*red = 255;
	if (*green > 255)
		*green = 255;
	if (*blue > 255)
		*blue = 255;
}

bool	check_turn(t_philosopher *me, t_philo_fork *low, t_philo_fork *high)
{
	bool	wait_turn;

	if (low == high)
		return (true);
	pthread_mutex_lock(&low->mutex);
	pthread_mutex_lock(&high->mutex);
	wait_turn = me->left_fork->first == LEFT;
	wait_turn |= me->right_fork->first == RIGHT;
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
