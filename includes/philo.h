/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:31:45 by esivre            #+#    #+#             */
/*   Updated: 2022/02/14 17:36:40 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h> 
# include <string.h> 
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define DIE 2
# define ALIVE 0

typedef struct s_data
{
	unsigned int	nbr_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nbr_max_eat;
	time_t			time_start;
	suseconds_t		time_start_ms;
}	t_data;

typedef struct s_mutex
{
	pthread_mutex_t	m_display;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_die;
	pthread_mutex_t	m_nbr_meal;
	int				die;
}	t_mutex;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	m_fork_l;
	pthread_mutex_t	*m_fork_r;
	pthread_t		pthread;
	int				nbr_meal;
	long long		t_last_eat;
	t_data			data;
	t_mutex			*mutex;
}	t_philo;

void				display_state_death(t_philo *philo, char *str);
int					ft_isdigit(int c);
char				*ft_strcat(char *dest, char *src);
void				ft_nbr_to_str(char *str, long long nb);
int					ft_atoi(const char *nbr);
int					ft_strlen(char *str);
int					ft_launch_philos(t_philo **philos, t_data data);
void				philo_sleep(t_philo *philo);
void				philo_eat(t_philo *philo);
int					ft_init_mutex(t_philo **philos,
						t_data data, t_mutex *mutex);
int					ft_init_philos(t_philo **philos,
						t_data data, t_mutex *mutex);
void				free_philos(t_philo **philos);
void				ft_destroy_mutex(t_philo **philos, t_data data);
int					_death(t_philo *philo);
int					_all_meal(t_philo philo);
int					check_nb_argc(int argc, char **argv);
int					ft_fill_data(int argc, char **argv, t_data *data);
void				display_state(t_philo *philo, char *str);
void				*start_routine(void *arg);
int					ft_error(int i);
void				monitor_end(t_philo **philo, t_data data);
long unsigned int	get_time(t_data data);
void				get_time_start(t_data *data);
long long			ft_get_time(void);
void				ft_sleep(int time);

#endif
