/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 02:19:52 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 05:32:37 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int eat_check(t_philo *philo)
{
    if (((get_time() - philo->last_meal) >= philo->infos->time_to_die))
        return (1);
    else
        return (0);
}

void satisfied(t_info *infos)
{
    infos->program_end = 1;
    printf("All the philosophers have eaten %d meals\n", infos->must_eat_time);
    pthread_mutex_unlock(&infos->print_mutex);
}

int death(t_info *infos, t_philo *philo, int *satisfied_philos)
{
    if (infos->must_eat_time > 0 && philo->meals >= infos->must_eat_time)
        *satisfied_philos += 1;
    if (eat_check(philo))
    {
        pthread_mutex_unlock(&infos->print_mutex);
        print(philo, DEAD);
        pthread_mutex_lock(&infos->print_mutex);
        infos->program_end = 1;
        pthread_mutex_unlock(&infos->print_mutex);
        return (1);
    }
    return (0);
}

void check_all(t_philo *philos, t_info *infos)
{
    int	satisfied_philos;
    int	i;

	satisfied_philos = 0;
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&infos->print_mutex);
		while(++i < infos->philo_nbr)
		{
			if(death(infos, &philos[i], &satisfied_philos))
				return ;
		}
		if (satisfied_philos == infos->philo_nbr)
			return(satisfied(infos));
		pthread_mutex_unlock(&infos->print_mutex);
	}
}

int threads_life(t_info *infos, t_philo *philos, pthread_mutex_t *forks)
{
	int i;

	i = -1;
	while (++i < infos->philo_nbr)
	{
		philos[i].start_time = get_time();
		if (pthread_create(&philos[i].thread_id, NULL, philo_life, (void *)&philos[i]) != 0)
		{
			failure(infos, forks, philos, "Erreur lors de la creations des threads");
			return (0);
		}
	}
	check_all(philos, infos);
	i = -1;
	while (++i < infos->philo_nbr)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
		{
			failure(infos, forks, philos, "Erreur lors du joignement des threads");
			return (0);
		}
	}
	return (1);
}