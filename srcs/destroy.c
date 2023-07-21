/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 00:50:09 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 03:27:03 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i += 1;
	return (i);
}

void    destroy(t_info *infos, pthread_mutex_t *forks, t_philo *philos)
{
    int i;

    if (infos)
        pthread_mutex_destroy(&infos->print_mutex);
    if (forks)
    {
        i = 0;
        while (i < infos->philo_nbr)
		{
			pthread_mutex_destroy(&forks[i]);
			philos[i].left_fork = NULL;
			philos[i].right_fork = NULL;
			i++;
		}
		free(forks);
		forks = NULL;
    }
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}

int	failure(t_info *infos, pthread_mutex_t *forks, t_philo *philos, char *msg)
{
	destroy(infos, forks, philos);
	printf("%s\n", msg);
	return (1);
}