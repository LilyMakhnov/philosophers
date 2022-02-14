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
		ft_sleep(philo->data.time_to_die);
		pthread_mutex_unlock(&philo->m_fork_l);
		usleep(1000);
		return ;
	}
	pthread_mutex_lock(philo->m_fork_r);
	display_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->mutex->m_eat);
	philo->t_last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->mutex->m_eat);
	display_state(philo, "is eating");
	ft_sleep(philo->data.time_to_eat);
	if (philo->nbr_meal > 0)
	{	
		pthread_mutex_lock(&(philo)->mutex->m_nbr_meal);
		philo->nbr_meal--;
		pthread_mutex_unlock(&(philo)->mutex->m_nbr_meal);
	}
	pthread_mutex_unlock(philo->m_fork_r);
	pthread_mutex_unlock(&philo->m_fork_l);
}

void	philo_eat_two(t_philo *philo)
{
	pthread_mutex_lock(philo->m_fork_r);
	display_state(philo, "has taken a fork");
	if (philo->data.nbr_philos == 1)
	{
		ft_sleep(philo->data.time_to_die);
		pthread_mutex_unlock(philo->m_fork_r);
		usleep(1000);
		return ;
	}
	pthread_mutex_lock(&philo->m_fork_l);
	display_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->mutex->m_eat);
	philo->t_last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->mutex->m_eat);
	display_state(philo, "is eating");
	ft_sleep(philo->data.time_to_eat);
	if (philo->nbr_meal > 0)
	{	
		pthread_mutex_lock(&(philo)->mutex->m_nbr_meal);
		philo->nbr_meal--;
		pthread_mutex_unlock(&(philo)->mutex->m_nbr_meal);
	}
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
	while (!_death(philo))
	{
		philo_eat(philo);
		if (!philo->nbr_meal)
			usleep(10);
		philo_sleep(philo);
		display_state(philo, "is thinking");
		if (philo->data.nbr_philos % 2)
			ft_sleep(philo->data.time_to_die / 4);
	}
	return (NULL);
}
