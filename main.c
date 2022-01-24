#include <unistd.h>
#include <stdlib.h> //atoi
#include <string.h> //memset
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	unsigned int	nbr_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nbr_max_eat;
	unsigned int	time_start;
}	t_data;

typedef struct s_philo
{
	int id;
	pthread_mutex_t *m_fork_l;
	pthread_mutex_t *m_fork_r;
	pthread_t	pthread;
	int status;
	int t_last_eat;
	t_data data;
}	t_philo;

unsigned int	get_time(unsigned int start)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((unsigned int)(current_time.tv_sec * 1000000 + current_time.tv_usec - start));
}

int	check_nb_argc(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "wrong numbers of arguments\n", 27);	
		return (1);
	}
	return (0);
}

//WARNING atoi and memset as to be replaced by ft_*()
int	ft_fill_data(int argc, char **argv, t_data *data)
{
	if (check_nb_argc(argc))
		return (1);
	memset(data, 0, sizeof(t_data));
	data->nbr_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->nbr_max_eat = atoi(argv[5]);
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

void	*start_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo*)arg;
	while (1)
	{
		pthread_mutex_lock(philo->m_fork_l);
		pthread_mutex_lock(philo->m_fork_r);
		printf("---%i ms %i takes the forks\n", get_time(philo->data.time_start)/1000, philo->id);
		printf("---%i eats\n", philo->id);
		usleep(philo->data.time_to_eat * 1000);
		pthread_mutex_unlock(philo->m_fork_l);
		pthread_mutex_unlock(philo->m_fork_r);
		printf("---%i take off the forks\n", philo->id);
		printf("---%i is sleeping\n", philo->id);
		usleep(philo->data.time_to_sleep * 1000);
		printf("---%i is thinking\n", philo->id);
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
	
	*philos = malloc(sizeof(t_philo) * data.nbr_philos);
	if (!philos)
		return (ft_error(1));
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
	
	if (ft_fill_data(argc, argv, &data) || ft_init_philos(&philos, data))
		return (1);
	data.time_start = get_time(0);
	i = -1;
	while (++i < (int)data.nbr_philos)
	{
		pthread_create(&philos[i].pthread, NULL, &start_routine, &philos[i]);
		usleep(10);
	}
	sleep(5);
	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_detach(philos[i].pthread);
	free_philos(&philos, data.nbr_philos);
	return (0);
}