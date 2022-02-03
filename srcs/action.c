#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	display_state(philo, "is sleeping");
	usleep(philo->data.time_to_sleep * 1000);
//	ft_sleep(philo, philo->data.time_to_sleep);
}

void	philo_eat(t_philo *philo)
{	
	pthread_mutex_lock(&philo->m_fork_l);
	display_state(philo, "has taken a fork");
	if (philo->m_fork_r != &philo->m_fork_l)
	{
		pthread_mutex_lock(philo->m_fork_r);	
		display_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->m_display);
		philo->t_last_eat = ft_get_time();
		pthread_mutex_unlock(philo->m_display);
		display_state(philo, "is eating");
		usleep(philo->data.time_to_eat * 1000);
//		ft_sleep(philo, philo->data.time_to_eat);
		pthread_mutex_unlock(philo->m_fork_r);
	}
	pthread_mutex_unlock(&philo->m_fork_l);
}