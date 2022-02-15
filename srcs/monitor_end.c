/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:17:06 by esivre            #+#    #+#             */
/*   Updated: 2022/02/14 11:18:46 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_death(t_philo **philo, t_data data)
{
	int	i[2];

	i[0] = -1;
	i[1] = 0;
	while (++i[0] < (int)data.nbr_philos)
	{
		pthread_mutex_lock(&(*philo)->mutex->m_eat);
		if (!(*philo)[i[0]].nbr_meal)
			i[1]++;
		if (ft_get_time() - (*philo)[i[0]].t_last_eat > data.time_to_die
			|| i[1] == (int)data.nbr_philos)
		{
			pthread_mutex_lock(&(*philo)->mutex->m_display);
			(*philo)->mutex->die = DIE;
			pthread_mutex_unlock(&(*philo)->mutex->m_display);
			pthread_mutex_unlock(&(*philo)->mutex->m_eat);
			pthread_mutex_lock(&(*philo)->mutex->m_display);
			if (i[1] == (int)data.nbr_philos)
				printf("Each philo ate at least %i times\n", data.nbr_max_eat);
			else
				display_state_no_mutex(&(*philo)[i[0]], "is dead");
			return ((void)pthread_mutex_unlock(&(*philo)->mutex->m_display));
		}
		pthread_mutex_unlock(&(*philo)->mutex->m_eat);
	}
}

void	monitor_end(t_philo **philo, t_data data)
{
	ft_sleep((*philo)->data.time_to_die / 2);
	while ((*philo)->mutex->die == ALIVE)
	{
		usleep(100);
		monitor_death(philo, data);
	}
}
