/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:56:14 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/21 13:14:53 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h" 

int	init_philo(t_infos *infos, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < infos->num)
	{
		philo[i].id = i;
		philo[i].dead = 0;
		philo[i].iter_num = 0;
		philo[i].thread_start = 0;
		philo[i].meal = 0;
		philo[i].infos = infos;
		philo[i].lf = &infos->fork[i];
		philo[i].rf = 0;
	}
	return (0);
}

static int	init_infos_mutex(t_infos *infos)
{
	int	i;

	i = -1;
	infos->death = malloc(sizeof(pthread_mutex_t));
	if (!infos->death)
		return (error_msg("Error\nMutex death: malloc failed\n", infos, 0, 1));
	infos->fork = malloc(sizeof(pthread_mutex_t) * infos->num);
	if (!infos->fork)
		return (error_msg("Error\nMutex fork: malloc failed\n", infos, 0, 1));
	if (pthread_mutex_init(infos->death, NULL) == -1)
		return (error_msg("Error\nMutex init failed\n", infos, 0, 1));
	while (++i < infos->num)
		if (pthread_mutex_init(&infos->fork[i], NULL) == -1)
			return (error_msg("Error\nMutex init failed\n", infos, 0, 1));
	return (0);
}

static int	init_infos(t_infos *infos, char **av)
{
	int	mutex;

	mutex = -1;
	infos->num = ft_atoi(av[1]);
	infos->time_to_die = ft_atoi(av[2]);
	infos->time_to_eat = ft_atoi(av[3]);
	infos->time_to_sleep = ft_atoi(av[4]);
	infos->max_iter = -2;
	infos->check_meal = 0;
	infos->start = 0;
	infos->ready = 0;
	infos->death = 0;
	infos->fork = 0;
	if (av[5])
	{
		infos->check_meal = 1;
		infos->max_iter = ft_atoi(av[5]);
	}
	infos->over = 0;
	if (infos->num > 0)
		mutex = init_infos_mutex(infos);
	return (mutex || infos->time_to_die <= 0 || infos->time_to_eat <= 0
		|| infos->time_to_sleep <= 0 || infos->max_iter == 0);
}

int	main(int ac, char **av)
{
	t_infos	infos;

	if (ac != 5 && ac != 6)
		return (error_msg("Error: invalid arguments\n", &infos, 0, 0));
	if (init_infos(&infos, av))
		return (error_msg("Error: invalid arguments\n", &infos, 0, 1));
	if (philo(&infos))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
