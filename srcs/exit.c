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

void	free_philos(t_philo **philos)
{
	free(*philos);
	*philos = NULL;
}

void	ft_destroy_mutex(t_philo **philos, t_data data)
{
	int	i;

	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_mutex_destroy(&(*philos)[i].m_fork_l);
	pthread_mutex_destroy(&(*philos)->mutex->m_nbr_meal);
	pthread_mutex_destroy(&(*philos)->mutex->m_die);
	pthread_mutex_destroy(&(*philos)->mutex->m_eat);
	pthread_mutex_destroy(&(*philos)->mutex->m_display);
}

int	_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->m_die);
	if (philo->mutex->die == DIE)
	{
		pthread_mutex_unlock(&philo->mutex->m_die);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex->m_die);
	return (0);
}

int	_all_meal(t_philo philo)
{
	pthread_mutex_lock(&philo.mutex->m_nbr_meal);
	if (philo.nbr_meal)
	{
		pthread_mutex_unlock(&philo.mutex->m_nbr_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo.mutex->m_nbr_meal);
	return (0);
}
