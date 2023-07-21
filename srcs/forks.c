/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 01:02:57 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 01:23:49 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void free_forks(pthread_mutex_t *forks, int max)
{
	int i;

	i = 0;
	while (i <= max)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

pthread_mutex_t *init_forks(t_info *infos)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(infos->philo_nbr * sizeof(pthread_mutex_t));
	if (!forks)
		failure(infos, NULL, NULL, "malloc error");
	i = 0;
	while (i < infos->philo_nbr)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			free_forks(forks, i);
			failure(infos, NULL, NULL, "mutex init error");
		}
		i++;
	}
	return (forks);
}