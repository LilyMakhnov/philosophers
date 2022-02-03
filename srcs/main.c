#include "philo.h"

int	check_nb_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "wrong numbers of arguments\n", 27);	
		return (1);
	}
	return (0);
}

int	ft_fill_data(int argc, char **argv, t_data *data)
{
	if (check_nb_argc(argc))
		return (1);
	ft_memset(data, 0, sizeof(t_data));	
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_max_eat = ft_atoi(argv[5]);
	return (0);		
}

void	display_state(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->m_display);
	if (!_death(*philo))
		printf("%li %i %s\n", get_time(philo->data), philo->id, str);
	pthread_mutex_unlock(philo->m_display);
}

void	*start_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo*)arg;
	display_state(philo, "is thinking");	
	if (philo->id % 2)
		usleep(philo->data.time_to_eat/10);	
	while (!_death(*philo))
	{
		if (!_death(*philo))
			philo_eat(philo);
		if (!_death(*philo))
			philo_sleep(philo);
		if (!_death(*philo))
			display_state(philo, "is thinking");
	}
	return (NULL);
}

int ft_error(int i)
{
	printf("Error\n");
	return (i);
}

void	monitor_end(t_philo **philo)
{
	int i;

	while (*(*philo)[0].die != DIE)
	{
		i = -1;
		while (++i < (int)(*philo)[0].data.nbr_philos)
		{
			pthread_mutex_lock((*philo)->m_display);
			if (ft_get_time() - (*philo)[i].t_last_eat >= (*philo)[i].data.time_to_die)
			{
				printf("%li %i %s\n", get_time((*philo)[i].data), (*philo)[i].id, "is dead");
				pthread_mutex_lock((*philo)->m_die);
				*(*philo)->die = DIE;
				pthread_mutex_unlock((*philo)->m_die);
				pthread_mutex_unlock((*philo)->m_display);
				break;
			}
			usleep(15);
			pthread_mutex_unlock((*philo)->m_display);
		}
	}
}

int main(int argc, char **argv)
{
	t_data data;
	t_philo *philos;
	int i;
	
	if (ft_fill_data(argc, argv, &data) || ft_init_philos(&philos, &data))
		return (1);
	i = -1;
	while (++i < (int)data.nbr_philos)
	{
		philos[i].t_last_eat = ft_get_time();
		pthread_create(&philos[i].pthread, NULL, &start_routine, &philos[i]);
		usleep(150);
	}
	monitor_end(&philos);
	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_join(philos[i].pthread, NULL);
	ft_destroy_mutex(&philos, data);
	free_philos(&philos);
	return (0);
}