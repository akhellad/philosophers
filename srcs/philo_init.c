/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:38:30 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 05:34:19 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo *init_philos(t_info *infos, pthread_mutex_t *forks)
{
    t_philo *philos;
	int		i;

	philos = malloc(infos->philo_nbr * sizeof(t_philo));
	if (!philos)
		failure(infos, forks, NULL, "malloc error");
	i = 0;
	while (i < infos->philo_nbr)
	{
		philos[i].id = i + 1;
		philos[i].meals = -1;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % infos->philo_nbr];
		philos[i].last_meal = get_time();
		philos[i].infos = infos;
		i++;
	}
	return (philos);
}