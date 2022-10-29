/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:01:18 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/29 15:50:49 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool	numeric_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				return (false);
			}
		}
	}
	return (true);
}

int	panic(char *msg, int errno)
{
	printf("ERROR: %s\n", msg);
	return (errno);
}

bool	ul_overflow(unsigned long before, unsigned long after)
{
	return (((before >> 63) & 1) && !((after >> 63) & 1));
}

unsigned long	*atoul(const char *string, unsigned long *location)
{
	size_t			i;
	unsigned long	accumulator;
	unsigned long	temp;

	i = 0;
	accumulator = 0;
	while (string[i])
	{
		temp = accumulator;
		accumulator *= 10;
		accumulator += string[i++] - '0';
		if (ul_overflow(temp, accumulator))
			return (NULL);
	}
	*location = accumulator;
	return (location);
}
