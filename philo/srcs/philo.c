/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:19:25 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/31 21:00:17 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


void	ft_status(t_data *data)
{
	int		i;
	long	tm_last_eat;

	i = 0;
	while(i < data->total_philo)
	{
		pthread_mutex_lock(&data->philos[i].mtx_eat);
		tm_last_eat = data->philos[i].time_last_eat;
		pthread_mutex_unlock(&data->philos[i].mtx_eat);
		if (ft_get_time(data->time_start) - 
			 tm_last_eat > data->time_to_die)
		{
			pthread_mutex_lock(&data->mtx_finished);
			data->finished = 1;
			pthread_mutex_unlock(&data->mtx_finished);
			ft_print_st("dead", &data->philos[i]);
			break;
		}
		if(data->lim_times_eaten != -1 && ft_are_full(data))
			break;
		i++;
		if(i == data->total_philo)
			i = 0;
	}
}

int	ft_are_full(t_data *data)
{
	int	full;

	pthread_mutex_lock(&data->mtx_philo_full);
	full = data->philos_full;
	pthread_mutex_unlock(&data->mtx_philo_full);
	if(full == data->total_philo)
	{
		pthread_mutex_lock(&data->mtx_finished);
		data->finished = 1;
		pthread_mutex_unlock(&data->mtx_finished);
		return(1);
	}
	return(0);
}

void	ft_finish(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->total_philo)
	{
		if(pthread_join(data->threads[i], NULL) != 0)
			ft_error(3);
		i++;
	}
	i = 0;
	while (i < data->total_philo)
	{
		pthread_mutex_destroy(&data->philos[i].right_fork);
		pthread_mutex_destroy(&data->philos[i].mtx_eat);
		i++;
	}
	pthread_mutex_destroy(&data->mtx_data);
	pthread_mutex_destroy(&data->mtx_write);
	pthread_mutex_destroy(&data->mtx_finished);
	pthread_mutex_destroy(&data->mtx_philo_full);
	free(data->philos);
	free(data->threads);
}

int	ft_init_philos(t_data *data)
{
	int	i;
	i = 0;
	while (i < data->total_philo)
	{
		data->philos[i].philo = i + 1;
		data->philos[i].time_last_eat = 0;
		data->philos[i].times_eaten = 0;
		pthread_mutex_init(&data->philos[i].right_fork, NULL);
		pthread_mutex_init(&data->philos[i].mtx_eat, NULL);
		data->philos[i].data = data;
		i++;
	}
	i = 1;
	data->philos[0].left_fork = &data->philos[data->total_philo - 1].right_fork;
	while (i < data->total_philo)
	{
		data->philos[i].left_fork = &data->philos[i - 1].right_fork;
		i++;
	}
	return(1);
}
int	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;

	while (i < data->total_philo)
	{
		if(pthread_create(&data->threads[i], NULL, &ft_routine, &(data)->philos[i]) !=0)
			return(0);
		i++;
	}
	return(1);
}

int	ft_init_data(t_data *data)
{
	pthread_mutex_init(&data->mtx_data, NULL);
	pthread_mutex_init(&data->mtx_write, NULL);
	pthread_mutex_init(&data->mtx_finished, NULL);
	pthread_mutex_init(&data->mtx_philo_full, NULL);
	pthread_mutex_lock(&data->mtx_data);
	data->philos_full = 0;
	data->finished = 0;
	data->philos = malloc(sizeof(t_philo) * data->total_philo);
	if(!data->philos)
		return (ft_error(2));
	data->threads = malloc(sizeof(pthread_t) * data->total_philo);
	if(!data->threads)
	{
		free(data->philos);
		return(ft_error(2));
	}
	if(!ft_init_philos(data))
		return(0);
	if(!ft_init_threads(data))
		return(0);
	return(1);
}

int	main(int argc, char **argv)
{
	t_data data;

	if(!ft_check_args(argc, argv, &data))
		return(1);
	if(!ft_init_data(&data))
		return(1);
	data.time_start = ft_get_time(0);
	pthread_mutex_unlock(&data.mtx_data);
	ft_status(&data);
	ft_finish(&data);
	return(0);
}