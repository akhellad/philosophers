/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 02:36:55 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 04:36:30 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

#define TAKE_FORK_STR "has taken a fork\n"
#define EAT_STR "is eating\n"
#define THINK_STR "is thinking\n"
#define SLEEP_STR "is sleeping\n"
#define DEAD_STR "is dead\n"

void    print(t_philo *philo, t_event_id event_id)
{
    long    timestamp;
    char    *events[5] = {DEAD_STR, EAT_STR, THINK_STR, SLEEP_STR, TAKE_FORK_STR};
    pthread_mutex_lock(&philo->infos->print_mutex);
    if(philo->infos->program_end)
    {
        pthread_mutex_unlock(&philo->infos->print_mutex);
        return ;
    }
    timestamp = get_time() - philo->start_time;
    printf("%ld %d %s", timestamp, philo->id, events[event_id]);
    pthread_mutex_unlock(&philo->infos->print_mutex);
}