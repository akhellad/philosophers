/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 11:59:01 by akhellad          #+#    #+#             */
/*   Updated: 2023/07/21 03:11:20 by akhellad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_info			info;
	pthread_mutex_t	*forks;
	t_philo			*philos;

	if (!check_args(ac, av) || init_infos(&info, av))
		return (0);
	forks = init_forks(&info);
	philos = init_philos(&info, forks);
	if (!threads_life(&info, philos, forks))
		return (1);
	destroy(&info, forks, philos);
	return (0);
}
