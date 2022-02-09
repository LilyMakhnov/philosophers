#include "philo.h"

int	ft_init_mutex(t_philo **philos, t_data *data)
{
	unsigned int i;

	pthread_mutex_init(&data->m_display, NULL);
	pthread_mutex_init(&data->m_die, NULL);
	pthread_mutex_init(&data->m_eat, NULL);
	i = -1;
	while (++i < data->nbr_philos)
	{
		(*philos)[i].data = data;
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
	int *die;
	
	*philos = malloc(sizeof(t_philo) * data->nbr_philos);
	if (!philos)
		return (ft_error(1));
	ft_memset(*philos, 0, sizeof(*philos));	
	die = malloc(sizeof(int));
	if (!die)
		return (free(philos), ft_error(1));
	*die = ALIVE;
	get_time_start(data);
	i = -1;
	while (++i < data->nbr_philos)
	{
		(*philos)[i].nbr_meal = data->nbr_max_eat;
		(*philos)[i].id = i + 1;
		(*philos)[i].die = die;
	}
	return (ft_init_mutex(philos, data));
}

int	ft_launch_philos(t_philo **philos)
{
	int i;

	i = -1;
	while (++i < (int)(*philos)[0].data->nbr_philos)
	{
		(*philos)[i].t_last_eat = ft_get_time();
		pthread_create(&(*philos)[i].pthread, NULL, &start_routine, &(*philos)[i]);
	}
	return (1);
}