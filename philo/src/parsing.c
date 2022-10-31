/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 18:01:18 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/31 14:23:47 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * @brief check whether or not all arguments supplied consist only of numerals
 *
 * @param argc	amount of arguments that the program receives from the shell
 * @param argv	array of string arguments that the program received from the
 *				shell
 * @return boolean representing whether or not all of our arguments are numeric
 */
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

/**
 * @brief print an error message to standard output, and return the error number
 *
 * @param msg	string to be printed to standard output
 * @param errno	error number to be returned back to the caller
 * @return errno
 */
int	panic(char *msg, int errno)
{
	printf("ERROR: %s\n", msg);
	return (errno);
}

/**
 * @brief detect whether or not an unsigned number has overflowed
 * @note	this is built on the fact that unsigned numbers overflow when the 
 *			most significant bit flips from 1 to 0
 * 
 * @param before	the number before the addition was invoked
 * @param after		the number after the addition was done
 * @return bool indicating overflow
 */
bool	ul_overflow(unsigned long before, unsigned long after)
{
	return (((before >> 63) & 1) && !((after >> 63) & 1));
}

/**
 * @brief parse string into number, assuming entire string is numeric
 *
 * @param string	string to parse
 * @param location	where to store the numerical value of the string
 * return location on successful parse, null pointer otherwise
 */
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
