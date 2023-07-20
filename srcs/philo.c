/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:59:01 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/09 17:09:39 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_thread(void *arg)
{
	t_philo	*philo;
	struct timeval	start_time;
	struct timeval	current_time;
	long			time_elapsed;

	philo = (t_philo *)arg;
	gettimeofday(&start_time, NULL);
	while (1)
	{
	    pthread_mutex_lock(&philo->death_flag_mutex);
    	if (philo->is_dead)
		{
    	    pthread_mutex_unlock(&philo->death_flag_mutex);
    	    break;
    	}
    	pthread_mutex_unlock(&philo->death_flag_mutex);
    	if (philo->id % 2 == 0) 
		{
        	pthread_mutex_lock(philo->left_fork.mutex);
        	print_status(philo->output_mutex, philo->id, "has taken a fork");
        	pthread_mutex_lock(philo->right_fork.mutex);
    	} 
		else 
		{
        	pthread_mutex_lock(philo->right_fork.mutex);
        	print_status(philo->output_mutex, philo->id, "has taken a fork");
        	pthread_mutex_lock(philo->left_fork.mutex);
    	}
		print_status(philo->output_mutex, philo->id, "is eating");
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork.mutex);
		pthread_mutex_unlock(philo->right_fork.mutex);
		print_status(philo->output_mutex, philo->id, "is sleeping");
		usleep(philo->time_to_sleep);
		print_status(philo->output_mutex, philo->id, "is thinking");

		gettimeofday(&current_time, NULL);
		time_elapsed = (current_time.tv_sec - start_time.tv_sec) * 1000 + (current_time.tv_usec - start_time.tv_usec) / 1000;
		if (time_elapsed >= philo->time_to_die)
		{
    		pthread_mutex_lock(&philo->death_flag_mutex);
    		philo->is_dead = 1;
    		pthread_mutex_unlock(&philo->death_flag_mutex);
    		print_status(philo->output_mutex, philo->id, "died");
    		break;
		}
	}
	return (NULL);
}

salut

int main(int ac, char **av)
{
	int philo_num;
	int i;
	pthread_mutex_t *forks;
	t_philo *philos;
	pthread_mutex_t output_mutex;

	if (ac == 4 || ac == 5)
	{
		i = 0;
		philo_num = ft_atoi(av[1]);
		philos = malloc(sizeof(t_philo) * philo_num);
		if (!philos)
			return (1);
		forks = malloc((philo_num + 1) * sizeof(pthread_mutex_t));
		if (!forks)
		{
			free(philos);
			return (1);
		}
    	while (i <= philo_num)
    	{
        	if (pthread_mutex_init(&forks[i], NULL) != 0)
        	{
        		free(forks);
            	free(philos);
            	return (1);
        	}
        	i++;
    	}
    	if (ac == 5)
    	{
        	if (pthread_mutex_init(&forks[philo_num], NULL) != 0)  // Initialisation du mutex supplémentaire pour le dernier philosophe
        	{
           		free(forks);
            	free(philos);
            	return (1);
        	}
    	}
		i = 0;
		if (pthread_mutex_init(&output_mutex, NULL) != 0)
			return (1);
		while (i < philo_num)
		{
			philos[i].id = i + 1;
			philos[i].left_fork.mutex = &forks[i];
			philos[i].right_fork.mutex = &forks[(i + 1) % philo_num];
			philos[i].time_to_eat = ft_atoi(av[3]);
			philos[i].time_to_sleep = ft_atoi(av[4]);
			philos[i].time_to_die = ft_atoi(av[2]);
			philos[i].output_mutex = &output_mutex;
			philos[i].is_dead = 0;
			if (pthread_create(&philos[i].thread, NULL, philo_thread, &philos[i]) != 0)
			{
				cleanall(philos, forks, philo_num);
				return (1);
			}
			if (pthread_mutex_init(&philos[i].death_flag_mutex, NULL) != 0)
        	{
            	cleanall(philos, forks, philo_num);
            	return (1);
        	}
			i++;
		}
		pthread_mutex_lock(&output_mutex);
		pthread_mutex_unlock(&output_mutex);
		cleanall(philos, forks, philo_num);
	}
	return (0);
}
