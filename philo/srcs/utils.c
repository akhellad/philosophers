/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:11:10 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 01:45:03 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi2(const char *nptr1, long int fin, long int neg)
{
	while (*nptr1 >= '0' && *nptr1 <= '9')
	{
		fin = fin * 10 + (*nptr1 - '0');
		nptr1 ++;
		if (fin > 2147483647)
		{
			if (neg > 0)
				return (-1);
			else
				return (0);
		}
	}
	return (fin * neg);
}

int	ft_atoi(const char *nptr)
{
	long int		fin;
	long int		neg;
	char			*nptr1;

	nptr1 = (char *)nptr;
	fin = 0;
	neg = 1;
	while (*nptr1 == ' ' || *nptr1 == '\f' || *nptr1 == '\n' || *nptr1 == '\r' \
	|| *nptr1 == '\t' || *nptr1 == '\v')
		nptr1 ++;
	if (*nptr1 == '+')
		nptr1 ++;
	else if (*nptr1 == '-')
	{
		neg = -1;
		nptr1 ++;
	}
	return (ft_atoi2(nptr1, fin, neg));
}

long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}
