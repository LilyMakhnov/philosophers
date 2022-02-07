#ifndef PHILO_H
# define PHILO_H

#include "libft.h"
#include <unistd.h>
#include <stdlib.h> //atoi
#include <string.h> //memset
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

# define DIE 2
# define ALIVE 0

typedef struct s_data
{
	unsigned int	nbr_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nbr_max_eat;
	pthread_mutex_t m_eat;
	pthread_mutex_t m_die;
	pthread_mutex_t m_display;
	time_t			time_start;
	suseconds_t		time_start_ms;
}	t_data;

typedef struct s_philo
{
	int id;
	pthread_mutex_t m_fork_l;
	pthread_mutex_t *m_fork_r;
	pthread_t	pthread;
	int *die;
	int status;
	long long t_last_eat;
	t_data *data;
}	t_philo;

int	ft_launch_philos(t_philo **philos);

void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);

int	ft_init_mutex(t_philo **philos, t_data *data);
int	ft_init_philos(t_philo **philos, t_data *data);

void	free_philos(t_philo **philos);
void	ft_destroy_mutex(t_philo **philos, t_data data);
int	verif_free(void *var);
int	_death(t_philo philo);

int	check_nb_argc(int argc);
int	ft_fill_data(int argc, char **argv, t_data *data);
void	display_state(t_philo *philo, char *str);
void	*start_routine(void *arg);
int ft_error(int i);
void	monitor_end(t_philo **philo);

//unsigned int	get_time(unsigned int start_s, unsigned int start_ms);
long unsigned int	get_time(t_data data);
//void	get_time_start(unsigned int *start_s, unsigned int *start_ms);
void	get_time_start(t_data *data);
long long	ft_get_time(void);
void	ft_sleep(/*t_philo *philo,*/ int time);

#endif