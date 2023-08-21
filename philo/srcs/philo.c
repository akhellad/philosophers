/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:05:06 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/21 13:15:45 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	check_meals(t_philo p, int last)
{
	if (p.infos->check_meal
		&& last == p.infos->num - 1
		&& p.iter_num == p.infos->max_iter)
		return (ft_usleep(300));
	return (0);
}

static void	check_philos(t_infos *infos, t_philo *philo)
{
	int	i;

	while (!infos->ready)
		continue ;
	while (!infos->over)
	{
		i = -1;
		while (++i < infos->num)
			if (check_death(&philo[i]) || check_meals(philo[i], i))
				infos->over = 1;
	}
	if (infos->check_meal && philo[infos->num - 1].iter_num == infos->max_iter)
	{
		ft_usleep(5 * infos->num);
		printf("						\n");
		printf("  All philosophers have eaten %d times\n", infos->max_iter);
		return ;
	}
	return ;
}

static int	init_thread(t_infos *infos, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < infos->num)
	{
		philo[i].rf = philo[(i + 1) % infos->num].lf;
		if (pthread_create(&philo[i].life_tid, NULL,
				&threads, &philo[i]) == -1)
			return (error_msg("Error\nFailed to create thread\n", \
					infos, philo, 2));
	}
	i = -1;
	infos->start = time_now();
	while (++i < infos->num)
	{
		philo[i].thread_start = infos->start;
		philo[i].meal = infos->start;
	}
	infos->ready = 1;
	return (0);
}

static void	join_threads(t_infos *infos, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < infos->num)
		pthread_join(philo[i].life_tid, (void *)&philo[i]);
	pthread_mutex_destroy(infos->death);
	pthread_mutex_destroy(infos->fork);
	free(infos->death);
	free(infos->fork);
	free(philo);
}

int	philo(t_infos *infos)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * infos->num);
	if (!philo || init_philo(infos, philo))
		return (EXIT_FAILURE);
	if (init_thread(infos, philo))
		return (EXIT_FAILURE);
	check_philos(infos, philo);
	join_threads(infos, philo);
	return (0);
}
