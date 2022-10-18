/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 08:19:15 by kalmheir          #+#    #+#             */
/*   Updated: 2022/10/18 09:47:47 by kalmheir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

bool numeric_args(int argc, char *argv[])
{
	int i;
	int j;
	
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf("%c,\n", argv[i][j]);
				return (false);
			}
		}
	}
	return (true);
}

int	panic(char *msg, int errno)
{
	printf("%s\n", msg);
	return (errno);
}

int main(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (panic("ERROR: Incorrect Number of Arguments!", 1));
	else if (!numeric_args(argc, argv))
		return (panic("ERROR: Please Only Use Numerical Arguments!", 2));
	else
	{
		return (0);
	}
}
