#include "philo.h"

void	get_time_start(t_data *data)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	//printf("seconde : %lu\n", current_time.tv_sec);
	//printf("micro-seconde : %lu\n", current_time.tv_usec);
	data->time_start = current_time.tv_sec;
	data->time_start_ms = current_time.tv_usec;
}

long unsigned int	get_time(t_data data)
{
	struct timeval	current_time;
	long long second;
	long long msecond;

	gettimeofday(&current_time, NULL);
	second = current_time.tv_sec - data.time_start;
	msecond = current_time.tv_usec - data.time_start_ms;
	return (second * 1000 + msecond / 1000);
}


long long	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec  * 1000 + current_time.tv_usec  / 1000);
}

void	ft_sleep(/*t_philo *philo,*/ int time)
{
	long long t;

	t = ft_get_time();
	while (ft_get_time() - t < time)
	{
//		if(!_death(*philo))
//			break;
		usleep(time/10);		
	}
}