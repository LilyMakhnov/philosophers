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
	int	i;

	i = -1;
	while (++i < (int)data.nbr_philos)
	{
		pthread_mutex_lock(&(*philo)->mutex->m_eat);
		if (ft_get_time() - (*philo)[i].t_last_eat >= data.time_to_die)
		{
			pthread_mutex_unlock(&(*philo)->mutex->m_eat);
			pthread_mutex_lock(&(*philo)->mutex->m_die);
			(*philo)->mutex->die = DIE;
			display_state_death(&(*philo)[i], "is dead");
			usleep(500);
			pthread_mutex_unlock(&(*philo)->mutex->m_die);
			break ;
		}
		pthread_mutex_unlock(&(*philo)->mutex->m_eat);
	}
}

void	monitor_nb_meals(t_philo **philo, t_data data)
{
	int				i;
	unsigned int	j;
	int				nb_eat;

	i = -1;
	j = 0;
	while (data.nbr_max_eat > -1 && ++i < (int)data.nbr_philos)
	{
		pthread_mutex_lock(&(*philo)->mutex->m_nbr_meal);
		nb_eat = (*philo)[i].nbr_meal;
		pthread_mutex_unlock(&(*philo)->mutex->m_nbr_meal);
		if (nb_eat == 0)
			j++;
		else
			break ;
		if (j == data.nbr_philos)
		{
			pthread_mutex_lock(&(*philo)->mutex->m_die);
			printf("Each philo ate at least %i times\n", data.nbr_max_eat);
			usleep(500);
			(*philo)->mutex->die = DIE;
			pthread_mutex_unlock(&(*philo)->mutex->m_die);
			break ;
		}
	}
}

void	monitor_end(t_philo **philo, t_data data)
{
	while (!_death((*philo)))
	{
		usleep(50);
		monitor_death(philo, data);
		if (_death((*philo)))
			break ;
		usleep(50);
		monitor_nb_meals(philo, data);
	}
}
