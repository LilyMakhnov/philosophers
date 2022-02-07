#include "philo.h"

void	free_philos(t_philo **philos)
{
	if((*philos)[0].die)
	{
		free((*philos)[0].die);
		(*philos)[0].die = NULL;
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
	pthread_mutex_destroy(&(*philos)[0].data->m_display);
	pthread_mutex_destroy(&(*philos)[0].data->m_die);
	pthread_mutex_destroy(&(*philos)[0].data->m_eat);
}

int	_death(t_philo philo)
{
	int ret;

	ret = 0;
	pthread_mutex_lock(&philo.data->m_die);
	if(*philo.die == DIE)
		ret = 1;
	pthread_mutex_unlock(&philo.data->m_die);
	return (ret);
}