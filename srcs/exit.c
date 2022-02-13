#include "philo.h"

void	free_philos(t_philo **philos)
{
	free(*philos);
	*philos = NULL;
}

void	ft_destroy_mutex(t_philo **philos, t_data data)
{
	int i;

	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_mutex_destroy(&(*philos)[i].m_fork_l);
	pthread_mutex_destroy(&(*philos)->mutex->m_nbr_meal);
	pthread_mutex_destroy(&(*philos)->mutex->m_die);
	pthread_mutex_destroy(&(*philos)->mutex->m_eat);
}

int	_death(t_philo philo)
{
	pthread_mutex_lock(&philo.mutex->m_die);
	if(philo.mutex->die == DIE)
	{
		pthread_mutex_unlock(&philo.mutex->m_die);
		return (1);
	}
	pthread_mutex_unlock(&philo.mutex->m_die);
	return (0);
}

int	_all_meal(t_philo philo)
{
	pthread_mutex_lock(&philo.mutex->m_nbr_meal);
	if(philo.nbr_meal)
	{
		pthread_mutex_unlock(&philo.mutex->m_nbr_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo.mutex->m_nbr_meal);
	return (0);
}
/*int	_death(t_philo philo)
{
	int is_die;

	is_die = 0;
	pthread_mutex_lock(&philo.mutex->m_die);
	is_die = philo.mutex->die;
	pthread_mutex_unlock(&philo.mutex->m_die);
	if(is_die == DIE)
		return (1);
	return (0);
}*/
/*
int	_all_meal(t_philo philo)
{
	int i;

	i = 0;
	pthread_mutex_lock(&philo.mutex->m_nbr_meal);
	i = philo.nbr_meal;
	pthread_mutex_unlock(&philo.mutex->m_nbr_meal);
	if(i)
		return (1);
	return (0);
}*/