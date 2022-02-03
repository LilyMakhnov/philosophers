#include "philo.h"

int	ft_init_mutex(t_philo **philos, t_data *data)
{
	unsigned int i;

	pthread_mutex_init((*philos)[0].m_display, NULL);
	pthread_mutex_init((*philos)[0].m_die, NULL);
	i = -1;
	while (++i < data->nbr_philos)
	{
		(*philos)[i].data = *data;
		(*philos)[i].id = i + 1;
		pthread_mutex_init(&(*philos)[i].m_fork_l, NULL);
	}
	i = -1;
	while (++i < data->nbr_philos)
		(*philos)[i].m_fork_r = &(*philos)[(i + 1) % data->nbr_philos].m_fork_l;
	return (0);
}

int	ft_init_philos(t_philo **philos, t_data *data)
{
	unsigned int i;
	pthread_mutex_t *m_display;
	pthread_mutex_t *m_die;
	int *die;
	
	*philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!philos)
		return (ft_error(1));
	ft_memset(*philos, 0, sizeof(*philos));	
	m_display = malloc(sizeof(pthread_mutex_t));
	m_die = malloc(sizeof(pthread_mutex_t));
	die = malloc(sizeof(int));
//	if (!m_display || !die)
//		return (verif_free(&m_display), verif_free(&die),
//			free(philos), ft_error(1));
	*die = ALIVE;
	get_time_start(data);
	i = -1;
	while (++i < data->nbr_philos)
	{
		(*philos)[i].die = die;
		(*philos)[i].m_display = m_display;
		(*philos)[i].m_die = m_die;
	}
	return (ft_init_mutex(philos, data));
}