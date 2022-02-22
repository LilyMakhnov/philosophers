/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 11:02:14 by esivre            #+#    #+#             */
/*   Updated: 2022/02/14 11:02:18 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nb_argc(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "wrong numbers of arguments\n", 27);
		return (1);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200)
		return (1);
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[2]) > 2147483647)
		return (1);
	if (ft_atoi(argv[3]) < 60 || ft_atoi(argv[3]) > 2147483647)
		return (1);
	if (ft_atoi(argv[4]) < 60 || ft_atoi(argv[4]) > 2147483647)
		return (1);
	if (argc == 6)
		if (ft_atoi(argv[5]) <= 0 || ft_atoi(argv[5]) > 2147483647)
			return (1);
	return (0);
}

int	ft_fill_data(int argc, char **argv, t_data *data)
{
	if (check_nb_argc(argc, argv))
		return (1);
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

void	display_state_no_mutex(t_philo *philo, char *str)
{
	char	to_print[50];

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
	char	to_print[50];

	pthread_mutex_lock(&philo->mutex->m_display);
	if (philo->mutex->die == ALIVE)
	{
		to_print[0] = 0;
		ft_nbr_to_str(to_print, get_time(philo->data));
		ft_strcat(to_print, " ");
		ft_nbr_to_str(to_print, philo->id);
		ft_strcat(to_print, " ");
		ft_strcat(to_print, str);
		ft_strcat(to_print, "\n");
		write(1, to_print, ft_strlen(to_print));
	}
	pthread_mutex_unlock(&philo->mutex->m_display);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_mutex	mutex;
	t_philo	*philos;
	int		i;

	if (ft_fill_data(argc, argv, &data)
		|| ft_init_philos(&philos, data, &mutex))
		return (write(2, "Error\n", ft_strlen("Error\n")), 1);
	ft_launch_philos(&philos, data);
	monitor_end(&philos, data);
	i = -1;
	while (++i < (int)data.nbr_philos)
		pthread_join(philos[i].pthread, NULL);
	ft_destroy_mutex(&philos, data);
	free(philos);
	return (0);
}
