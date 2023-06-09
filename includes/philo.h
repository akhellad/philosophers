/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:58:53 by akhellad          #+#    #+#             */
/*   Updated: 2023/06/09 17:04:56 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	*mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	t_fork		left_fork;
	t_fork		right_fork;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	pthread_t		thread;
	pthread_mutex_t *output_mutex;
	pthread_mutex_t death_flag_mutex;
	int				is_dead;
}	t_philo;

int	ft_atoi(const char *nptr);
void	cleanall(t_philo *philos, pthread_mutex_t *forks, int num_philos);
void	print_status(pthread_mutex_t *mutex, int id, const char *message);

#endif