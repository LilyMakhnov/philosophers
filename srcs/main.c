#include "philo.h"

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int len_dest;

	len_dest = 0;
	while (dest[len_dest])
		len_dest++;
	i = 0;
	while (src[i])
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (dest);
}

void	ft_nbr_to_str(char *str, long long nb)
{
	char a;

	if( nb > 9)
	{
		ft_nbr_to_str(str, nb / 10);
		nb = nb % 10;
	}
	a = nb + '0';
	ft_strcat(str, &a);
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
	else 
		data->nbr_max_eat = -1;
	return (0);		
}

void	display_state(t_philo *philo, char *str)
{
	char to_print[100];

	if (!_death(*philo))
	{
		to_print[0] = 0;
		ft_nbr_to_str(to_print, get_time(*philo->data));
		ft_strcat(to_print, " ");
		ft_nbr_to_str(to_print, philo->id);
		ft_strcat(to_print, " ");
		ft_strcat(to_print, str);
		ft_strcat(to_print, "\n");
		write(1, to_print, ft_strlen(to_print));
	}
}

void	*start_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo*)arg;
	ft_sleep(10);	
	display_state(philo, "is thinking");	
	if (philo->id % 2)
		ft_sleep(philo->data->time_to_eat/2);	
	while (!_death(*philo) && philo->nb_eat)
	{
		if (!_death(*philo))
			philo_eat(philo);
		if (!_death(*philo))
			philo_sleep(philo);
		if (!_death(*philo))
		{
			display_state(philo, "is thinking");
			if (ft_get_time()-philo->t_last_eat < philo->data->time_to_die / 2)
				ft_sleep(philo->data->time_to_die / 4);
		}
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
	long long t_eat;

	while (!_death((*philo[0]))) //*(*philo)[0].die //!_death((*philo[0]))
	{
		i = -1;
		while (++i < (int)(*philo)[0].data->nbr_philos)
		{
			pthread_mutex_lock(&(*philo)->data->m_eat);
			t_eat = (*philo)[i].t_last_eat;
			pthread_mutex_unlock(&(*philo)->data->m_eat);
			if (ft_get_time() - t_eat >= (*philo)[i].data->time_to_die)
			{
				pthread_mutex_lock(&(*philo)->data->m_die);
				printf("%li %i %s\n", get_time(*(*philo)[i].data), (*philo)[i].id, "is dead");
				*(*philo)->die = DIE;
				pthread_mutex_unlock(&(*philo)->data->m_die);
				break;
			}
			pthread_exit
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
	ft_launch_philos(&philos);
	monitor_end(&philos);
	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_join(philos[i].pthread, NULL);
	ft_destroy_mutex(&philos, data);
	free_philos(&philos);
	return (0);
}