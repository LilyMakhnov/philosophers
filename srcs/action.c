/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:00:44 by esivre            #+#    #+#             */
/*   Updated: 2022/02/14 11:00:48 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	display_state(philo, "is sleeping");
	ft_sleep(philo->data.time_to_sleep);
}

void	philo_eat_one(t_philo *philo)
{	
	pthread_mutex_lock(&philo->m_fork_l);
	display_state(philo, "has taken a fork");
	if (philo->data.nbr_philos == 1)
	{
		ft_sleep(2 * philo->data.time_to_die);
		return ((void)pthread_mutex_unlock(&philo->m_fork_l));
	}
	pthread_mutex_lock(philo->m_fork_r);
	pthread_mutex_lock(&philo->mutex->m_eat);
	pthread_mutex_lock(&philo->mutex->m_display);
	if (philo->mutex->die == ALIVE)
	{
		display_state_no_mutex(philo, "has taken a fork");
		philo->t_last_eat = ft_get_time();
		display_state_no_mutex(philo, "is eating");
	}
	pthread_mutex_unlock(&philo->mutex->m_display);
	pthread_mutex_unlock(&philo->mutex->m_eat);
	ft_sleep(philo->data.time_to_eat);
	pthread_mutex_lock(&philo->mutex->m_eat);
	if (philo->nbr_meal > 0)
		philo->nbr_meal--;
	pthread_mutex_unlock(&philo->mutex->m_eat);
	pthread_mutex_unlock(philo->m_fork_r);
	pthread_mutex_unlock(&philo->m_fork_l);
}

void	philo_eat_two(t_philo *philo)
{
	pthread_mutex_lock(philo->m_fork_r);
	display_state(philo, "has taken a fork");
	if (philo->data.nbr_philos == 1)
	{
		ft_sleep(2 * philo->data.time_to_die);
		return ((void)pthread_mutex_unlock(philo->m_fork_r));
	}
	pthread_mutex_lock(&philo->m_fork_l);
	pthread_mutex_lock(&philo->mutex->m_eat);
	pthread_mutex_lock(&philo->mutex->m_display);
	if (philo->mutex->die == ALIVE)
	{	
		display_state_no_mutex(philo, "has taken a fork");
		philo->t_last_eat = ft_get_time();
		display_state_no_mutex(philo, "is eating");
	}
	pthread_mutex_unlock(&philo->mutex->m_display);
	pthread_mutex_unlock(&philo->mutex->m_eat);
	ft_sleep(philo->data.time_to_eat);
	pthread_mutex_lock(&philo->mutex->m_eat);
	if (philo->nbr_meal > 0)
		philo->nbr_meal--;
	pthread_mutex_unlock(&philo->mutex->m_eat);
	pthread_mutex_unlock(&philo->m_fork_l);
	pthread_mutex_unlock(philo->m_fork_r);
}

void	philo_eat(t_philo *philo)
{	
	if (philo->id % 2)
		philo_eat_one(philo);
	else
		philo_eat_two(philo);
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	display_state(philo, "is thinking");
	if (!(philo->id % 2))
		ft_sleep(philo->data.time_to_eat / 2);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		pthread_mutex_lock(&philo->mutex->m_display);
		if (philo->mutex->die == ALIVE)
		{
			display_state_no_mutex(philo, "is thinking");
			pthread_mutex_unlock(&philo->mutex->m_display);
		}
		else
		{
			pthread_mutex_unlock(&philo->mutex->m_display);
			break ;
		}
		if (philo->data.nbr_philos % 2)
			ft_sleep(philo->data.time_to_die / 4);
	}
	return (NULL);
}
