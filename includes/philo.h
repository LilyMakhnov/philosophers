#ifndef PHILO_H
# define PHILO_H

#include "libft.h"
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
	time_t			time_start;
	suseconds_t		time_start_ms;
}	t_data;

typedef struct s_philo
{
	int id;
	pthread_mutex_t *m_fork_l;
	pthread_mutex_t *m_fork_r;
    pthread_mutex_t *m_display;
	pthread_t	pthread;
	int status;
	int t_last_eat;
	t_data data;
}	t_philo;

//unsigned int	get_time(unsigned int start_s, unsigned int start_ms);
long unsigned int	get_time(t_data data);
//void	get_time_start(unsigned int *start_s, unsigned int *start_ms);
void	get_time_start(t_data *data);
long long	ft_get_time(void);

#endif