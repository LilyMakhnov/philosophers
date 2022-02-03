#include "philo.h"

void	free_philos(t_philo **philos)
{
	if((*philos)[0].m_display)
	{
		free((*philos)[0].m_display);
		(*philos)[0].m_display = NULL;
	}
	if((*philos)[0].die)
	{
		free((*philos)[0].die);
		(*philos)[0].die = NULL;
	}
	if((*philos)[0].m_die)
	{
		free((*philos)[0].m_die);
		(*philos)[0].m_die = NULL;
	}
	free(*philos);
	*philos = NULL;
}

void	ft_destroy_mutex(t_philo **philos, t_data data)
{
	int i;

	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_mutex_destroy(&(*philos)[i].m_fork_l);
	pthread_mutex_destroy((*philos)[0].m_display);
	pthread_mutex_destroy((*philos)[0].m_die);
}

int	verif_free(void *var)
{
	if (var)
	{
		free(var);
		var = NULL;
		return (0);
	}
	return (1);
}

int	_death(t_philo philo)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(philo.m_die);
	if(*philo.die == DIE)
		ret = 1;
	pthread_mutex_unlock(philo.m_die);
	return (ret);
}