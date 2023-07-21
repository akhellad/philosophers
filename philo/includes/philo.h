/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:58:53 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 03:29:02 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_info
{
	int				philo_nbr;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_eat_time;
	pthread_mutex_t	print_mutex;
	int				program_end;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread_id;
	long			last_meal;
	long			start_time;
	t_info			*infos;
}		t_philo;

typedef enum e_event_id {
	DEAD,
	EAT,
	THINK,
	SLEEP,
	FORK,
}				t_event_id;

/*args.c*/
int				init_infos(t_info *infos, char **argv);
int				check_args(int ac, char **av);

/*utils.c*/
int				ft_atoi(const char *nptr);
long			get_time(void);

/*destroy.c*/
void			destroy(t_info *infos, pthread_mutex_t *forks, t_philo *philos);
int				failure(t_info *infos, pthread_mutex_t *forks, t_philo *philos, \
						char *msg);

/*forks.c*/
pthread_mutex_t	*init_forks(t_info *infos);

/*philo_init.c*/
t_philo			*init_philos(t_info *infos, pthread_mutex_t *forks);

/*print.c*/
void			print(t_philo *philo, t_event_id event_id);

/*philo_life.c*/
void			*philo_life(void *_philo);

/*threads.c*/
int				threads_life(t_info *infos, t_philo *philos, \
				pthread_mutex_t *forks);
void			satisfied(t_info *infos);

#endif