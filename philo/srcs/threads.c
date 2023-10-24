/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:12:34 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/21 13:14:56 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	someone_died(t_philo *p)
{
	print(p, DIE);
	p->infos->over = 1;
	p->dead = 1;
	pthread_mutex_unlock(p->lf);
	pthread_mutex_unlock(p->rf);
	return (1);
}

int	check_death(t_philo *p)
{
	long int	now;

	pthread_mutex_lock(p->infos->death);
	now = time_now() - p->meal;
	if (now >= p->infos->time_to_die)
	{
		pthread_mutex_unlock(p->infos->death);
		return (someone_died(p));
	}
	pthread_mutex_unlock(p->infos->death);
	return (0);
}

void	sleep_and_think(t_philo *p)
{
	print(p, SLEEP);
	ft_usleep(p->infos->time_to_sleep);
	print(p, THINK);
}

void	eat(t_philo *p)
{
	pthread_mutex_lock(p->lf);
	print(p, FORK);
	pthread_mutex_lock(p->rf);
	print(p, FORK);
	p->meal = time_now();
	print(p, EAT);
	ft_usleep(p->infos->time_to_eat);
	p->iter_num++;
	pthread_mutex_unlock(p->lf);
	pthread_mutex_unlock(p->rf);
}

void	*threads(void *job)
{
	t_philo	*p;

	p = (t_philo *)job;
	while (!p->infos->ready)
		continue ;
	if (p->id & 1)
		ft_usleep(p->infos->time_to_eat * 0.9 + 1);
	while (!p->infos->over)
	{
		eat(p);
		sleep_and_think(p);
	}
	return (NULL);
}
