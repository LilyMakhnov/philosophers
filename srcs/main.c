#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nbr)
{
	unsigned long	res;
	int				sign;

	res = 0;
	sign = 1;
	while (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
		if (*nbr++ == '-')
			sign *= -1;
	while (ft_isdigit(*nbr))
	{
		 if (res >= 922337203685477580 && sign == 1)
			 return (-1);
		 if (res >= 922337203685477580 && sign == -1)
			 return (0);
		res = res * 10 + *nbr++ - '0';
	}
	return (sign * res);
}

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
	//memset(data, 0, sizeof(t_data));	
	data->nbr_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_max_eat = ft_atoi(argv[5]);
	else 
		data->nbr_max_eat = -1;
	get_time_start(data);	
	return (0);		
}

void	display_state_death(t_philo *philo, char *str)
{
	char to_print[100];

	to_print[0] = 0;
	ft_nbr_to_str(to_print, get_time(philo->data));
	ft_strcat(to_print, " ");
	ft_nbr_to_str(to_print, philo->id);
	ft_strcat(to_print, " ");
	ft_strcat(to_print, str);
	ft_strcat(to_print, "\n");
	write(1, to_print, ft_strlen(to_print));
}

void	display_state(t_philo *philo, char *str)
{
	char to_print[100];

	if (!_death(*philo))
	{
		to_print[0] = 0;
		pthread_mutex_lock(&(*philo).mutex->m_eat);
		ft_nbr_to_str(to_print, get_time(philo->data));
		pthread_mutex_unlock(&(*philo).mutex->m_eat);
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
	display_state(philo, "is thinking");	
	if (philo->id % 2 || philo->id == (int)philo->data.nbr_philos)
		ft_sleep(philo->data.time_to_eat / 2);	
	while (!_death(*philo) && _all_meal(*philo))
	{
			philo_eat(philo);
			philo_sleep(philo);
			display_state(philo, "is thinking");
	}
	return (NULL);
}

int ft_error(int i)
{
	printf("Error\n");
	return (i);
}

void	monitor_death(t_philo **philo, t_data data)
{
	int i;

	i = -1;
	while (++i < (int)data.nbr_philos)
	{	
		pthread_mutex_lock(&(*philo)->mutex->m_eat);
		if (ft_get_time() - (*philo)[i].t_last_eat >= data.time_to_die)
		{
			pthread_mutex_unlock(&(*philo)->mutex->m_eat);
			pthread_mutex_lock(&(*philo)->mutex->m_die);
			display_state_death(&(*philo)[i], "is dead");
			(*philo)->mutex->die = DIE;
			pthread_mutex_unlock(&(*philo)->mutex->m_die);
			break;
		}
		pthread_mutex_unlock(&(*philo)->mutex->m_eat);
	}
}

void	monitor_nb_meals(t_philo **philo, t_data data)
{
	int i;
	unsigned int j;
	int nb_eat;

	i = -1;
	j = 0;
	while (data.nbr_max_eat > -1 && ++i < (int)data.nbr_philos)
	{
		pthread_mutex_lock(&(*philo)->mutex->m_nbr_meal);
		nb_eat = (*philo)[i].nbr_meal;
		pthread_mutex_unlock(&(*philo)->mutex->m_nbr_meal);
		if (nb_eat == 0)
			j++;
		else 
			break;
		if (j == data.nbr_philos)
		{
			pthread_mutex_lock(&(*philo)->mutex->m_die);
			printf("done\n");
			(*philo)->mutex->die = DIE;
			pthread_mutex_unlock(&(*philo)->mutex->m_die);
			break;
		}
	}
}

int	__death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->m_die);
	if(philo->mutex->die == DIE)
	{
		pthread_mutex_unlock(&philo->mutex->m_die);
		return (1);
	}
	pthread_mutex_unlock(&philo->mutex->m_die);
	return (0);
}

void	monitor_end(t_philo **philo, t_data data)
{
	while (!__death((*philo))) 
	{
		monitor_death(philo, data);
		monitor_nb_meals(philo, data);
	}
}

int main(int argc, char **argv)
{
	t_data data;
	t_mutex mutex;
	t_philo *philos;
	int i;
	
	if (ft_fill_data(argc, argv, &data) || ft_init_philos(&philos, data, &mutex))
		return (1);
	ft_launch_philos(&philos, data);
	monitor_end(&philos, data);
	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_join(philos[i].pthread, NULL);
	ft_destroy_mutex(&philos, data);
	free_philos(&philos);
	return (0);
}