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

//WARNING memset as to be replaced by ft_*()
int	ft_fill_data(int argc, char **argv, t_data *data)
{
	if (check_nb_argc(argc))
		return (1);
//	memset(data, 0, sizeof(t_data));
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_max_eat = ft_atoi(argv[5]);
	return (0);		
}

void	free_philos(t_philo **philos, unsigned int i)
{
	unsigned int j;

	j = 0;
	while (*philos && j < i)
			free((*philos)[j++].m_fork_l);
	free(*philos);
	*philos = NULL;
}

void	*time_eat(void *arg)
{
	long long st;
	long long i;
	t_philo *philo;

	st = ft_get_time();
	philo = (t_philo*)arg;
	i = 0;
	while (i < philo->data.time_to_die)
	{
		i = ft_get_time() - st;
	}
	printf("dead : %llu, philo %i\n", i, philo->id);
	write(1, "DEAD\n", 5);
	return (NULL);
}

void	*start_routine(void *arg)
{
	t_philo *philo;
	pthread_t p_time;
	
	philo = (t_philo*)arg;
	pthread_create(&p_time, NULL, &time_eat, philo);
	pthread_mutex_lock(philo->m_display);
	printf("---%lu ms %i is sleeping\n",get_time(philo->data),  philo->id);
	pthread_mutex_unlock(philo->m_display);
	usleep(philo->data.time_to_sleep * 1000);
	pthread_mutex_lock(philo->m_display);
	printf("---%lu ms %i is thinking\n", get_time(philo->data), philo->id);
	pthread_mutex_unlock(philo->m_display);
	while (1)
	{
		pthread_mutex_lock(philo->m_fork_l);
		pthread_mutex_lock(philo->m_fork_r);
		pthread_detach(p_time);
		pthread_create(&p_time, NULL, &time_eat, philo);
		pthread_mutex_lock(philo->m_display);
		printf("---%lu ms %i takes the forks\n", get_time(philo->data), philo->id);
		printf("---%lu ms %i eats\n", get_time(philo->data), philo->id);
		pthread_mutex_unlock(philo->m_display);
		usleep(philo->data.time_to_eat * 1000);
		pthread_mutex_lock(philo->m_display);
		pthread_mutex_unlock(philo->m_fork_l);
		pthread_mutex_unlock(philo->m_fork_r);
		printf("---%lu ms %i take off the forks\n", get_time(philo->data), philo->id);
		printf("---%lu ms %i is sleeping\n",get_time(philo->data),  philo->id);
		pthread_mutex_unlock(philo->m_display);
		usleep(philo->data.time_to_sleep * 1000);
		pthread_mutex_lock(philo->m_display);
		printf("---%lu ms %i is thinking\n", get_time(philo->data), philo->id);
		pthread_mutex_unlock(philo->m_display);
	}
	return (NULL);
}

int ft_error(int i)
{
	printf("Error\n");
	return (i);
}

int	ft_init_philos(t_philo **philos, t_data data)
{
	unsigned int i;
	pthread_mutex_t *m_display;
	
	*philos = malloc(sizeof(t_philo) * data.nbr_philos);
	if (!philos)
		return (ft_error(1));
	m_display = malloc(sizeof(pthread_mutex_t));
	if (!m_display)
	{
		free(philos);
		return (ft_error(1));
	}
	pthread_mutex_init(m_display, NULL);
	i = -1;
	while (++i < data.nbr_philos)
	{
		(*philos)[i].data = data;
		(*philos)[i].id = i + 1;
		(*philos)[i].m_fork_l = malloc(sizeof(pthread_mutex_t));
		if (!(*philos)[i].m_fork_l)
		{
			free_philos(philos, i);
			return (ft_error(1));
		}
		(*philos)[i].m_display = m_display;
		pthread_mutex_init((*philos)[i].m_fork_l, NULL);
	}
	i = -1;
	while (++i < data.nbr_philos)
		(*philos)[i].m_fork_r = (*philos)[(i + 1) % data.nbr_philos].m_fork_l;
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;
	t_philo *philos;
	int i;
	
	get_time_start(&data);
	sleep(2);
	if (ft_fill_data(argc, argv, &data) || ft_init_philos(&philos, data))
		return (1);
	i = -1;
	while (++i < (int)data.nbr_philos)
	{
		pthread_create(&philos[i].pthread, NULL, &start_routine, &philos[i]);
		usleep(10);
	}
	while (1)
	{
		sleep(1);
	}
	sleep(5);
	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_detach(philos[i].pthread);
	free_philos(&philos, data.nbr_philos);
	return (0);
}