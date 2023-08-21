/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:16:51 by akhellad          #+#    #+#             */
/*   Updated: 2023/08/21 13:14:05 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	error_msg(char *s, t_infos *infos, t_philo *p, int malloc)
{
	if (malloc)
	{
		if (infos->death != 0)
			free(infos->death);
		if (infos->fork != 0)
			free(infos->fork);
		if (p)
			free(p);
	}
	return (printf("%s", s));
}

void	print(t_philo *p, char *action)
{
	pthread_mutex_lock(p->infos->death);
	if (p->infos->over)
	{
		pthread_mutex_unlock(p->infos->death);
		return ;
	}
	printf("%ld %d %s\n", time_now() - p->thread_start,
		p->id, action);
	pthread_mutex_unlock(p->infos->death);
}
