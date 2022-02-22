/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:19:58 by esivre            #+#    #+#             */
/*   Updated: 2022/02/14 11:20:01 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_philo **philos, t_data data, t_mutex *mutex)
{
	unsigned int	i;

	pthread_mutex_init(&mutex->m_eat, NULL);
	pthread_mutex_init(&mutex->m_display, NULL);
	mutex->die = ALIVE;
	i = -1;
	while (++i < data.nbr_philos)
	{
		(*philos)[i].data = data;
		(*philos)[i].mutex = mutex;
		pthread_mutex_init(&(*philos)[i].m_fork_l, NULL);
	}
	i = -1;
	while (++i < data.nbr_philos)
		(*philos)[i].m_fork_r = &(*philos)[(i + 1) % data.nbr_philos].m_fork_l;
	return (0);
}

int	ft_init_philos(t_philo **philos, t_data data, t_mutex *mutex)
{
	unsigned int	i;

	*philos = malloc(sizeof(t_philo) * data.nbr_philos);
	if (!philos)
	{
		write(1, "Error\n", ft_strlen("Error\n"));
		return (1);
	}
	memset(*philos, 0, sizeof(philos) * data.nbr_philos);
	i = -1;
	while (++i < data.nbr_philos)
	{
		(*philos)[i].nbr_meal = data.nbr_max_eat;
		(*philos)[i].id = i + 1;
	}
	return (ft_init_mutex(philos, data, mutex));
}

int	ft_launch_philos(t_philo **philos, t_data data)
{
	int	i;

	i = -1;
	while (++i < (int)data.nbr_philos)
		(*philos)[i].t_last_eat = ft_get_time();
	i = -1;
	pthread_mutex_lock(&(*philos)->mutex->m_display);
	while (++i < (int)data.nbr_philos / 2)
	{
		(*philos)[i].t_last_eat = ft_get_time();
		pthread_create(&(*philos)[i].pthread, NULL,
			&start_routine, &(*philos)[i]);
		(*philos)[(int)data.nbr_philos - 1 - i].t_last_eat = ft_get_time();
		pthread_create(&(*philos)[(int)data.nbr_philos - 1 - i].pthread, NULL,
			&start_routine, &(*philos)[(int)data.nbr_philos - 1 - i]);
	}
	if ((int)data.nbr_philos % 2)
	{
		(*philos)[(int)data.nbr_philos / 2].t_last_eat = ft_get_time();
		pthread_create(&(*philos)[(int)data.nbr_philos / 2].pthread, NULL,
			&start_routine, &(*philos)[(int)data.nbr_philos / 2]);
	}
	pthread_mutex_unlock(&(*philos)->mutex->m_display);
	return (1);
}
