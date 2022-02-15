/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:56:27 by esivre            #+#    #+#             */
/*   Updated: 2022/02/14 10:56:32 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_philo **philos, t_data data)
{
	int	i;

	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_mutex_destroy(&(*philos)[i].m_fork_l);
	pthread_mutex_destroy(&(*philos)->mutex->m_eat);
	pthread_mutex_destroy(&(*philos)->mutex->m_display);
}
