/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:48:38 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 05:19:27 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

#define ERR "nbr_of_philosophers and must_eat_times must be bigger than 0"

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	check_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_is_digit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_args(int ac, char **av)
{
	if ((ac != 5 && ac != 6) || !check_digits(av))
	{
		failure(NULL, NULL, NULL, "Invalid arguments");
		return (0);
	}
	return (1);
}

int	init_infos(t_info *infos, char **argv)
{
	infos->philo_nbr = ft_atoi(argv[1]);
	infos->time_to_die = ft_atoi(argv[2]);
	infos->time_to_eat = ft_atoi(argv[3]);
	infos->time_to_sleep = ft_atoi(argv[4]);
	infos->must_eat_time = -1;
	if (argv[5])
		infos->must_eat_time = ft_atoi(argv[5]);
	if (infos->philo_nbr == 0 || infos->must_eat_time == 0)
	{
		failure(NULL, NULL, NULL, ERR);
		return (1);
	}
	if (pthread_mutex_init(&infos->print_mutex, NULL) != 0)
	{
		failure(NULL, NULL, NULL, ERR);
		return (1);
	}
	infos->program_end = 0;
	return (0);
}
