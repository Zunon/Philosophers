/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:53:27 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/29 19:10:50 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

t_milliseconds	get_time_in_ms(t_timeval then)
{
	t_timeval			now;

	gettimeofday(&now, NULL);
	return (1000 * (now.tv_sec - then.tv_sec) + (now.tv_usec - then.tv_usec) / 1000);
}
