/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:52:32 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/21 13:13:39 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define LEFT 0
# define RIGHT 1

typedef struct s_infos
{
	int				num;
	int				ready;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_iter;
	int				check_meal;
	int				over;
	long int		start;
	pthread_mutex_t	*death;
	pthread_mutex_t	*fork;
}	t_infos;

typedef struct s_philo
{
	int				id;
	int				dead;
	int				iter_num;
	long int		thread_start;
	long int		meal;
	pthread_t		life_tid;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	t_infos			*infos;
}	t_philo;

/*ft_atoi.c*/
int			ft_atoi(const char *str);

/*main.c*/
int			init_philo(t_infos *infos, t_philo *philo);

/*time.c*/
int			ft_usleep(long int time);
long int	time_now(void);

/*utils.c*/
int			error_msg(char *s, t_infos *infos, t_philo *p, int malloc);
void		print(t_philo *p, char *action);

/*philo.c*/
int			philo(t_infos *infos);

/*threads.c*/
int			check_death(t_philo *p);
void		*threads(void *job);

#endif