/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 02:52:32 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 04:40:29 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	pick_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, FORK);
		pthread_mutex_lock(philo->right_fork);
		print(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print(philo, FORK);
		pthread_mutex_lock(philo->left_fork);
		print(philo, FORK);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

void    eat(t_philo *philo)
{
    pick_forks(philo);
    pthread_mutex_lock(&philo->infos->print_mutex);
    philo->last_meal = get_time();
    philo->meals += 1;
    pthread_mutex_unlock(&philo->infos->print_mutex);
    print(philo, EAT);
    usleep(philo->infos->time_to_eat * 1000);
    drop_forks(philo);
}

void    sleeping(t_philo *philo)
{
    print(philo, SLEEP);
    usleep(philo->infos->time_to_sleep * 1000);
}

void *philo_life(void *_philo)
{
    t_philo *philo;
    philo = (t_philo *)_philo;
    if (philo->infos->philo_nbr == 1)
    {
        print(philo, FORK);
        return (NULL);
    }
    while (1)
    {
        pthread_mutex_lock(&philo->infos->print_mutex);
        if(philo->infos->program_end)
        {
            pthread_mutex_unlock(&philo->infos->print_mutex);
            break ;
        }
        pthread_mutex_unlock(&philo->infos->print_mutex);
        eat(philo);
        sleeping(philo);
        print(philo, THINK);
    }
    return (NULL);
}