/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:19:25 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/29 04:13:17 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"


void	ft_status(t_data *data)
{
	int		finished;
	int		i;
	int		full;

	i = 0;
	finished = 0;
	while(finished == 0)
	{
		if (ft_is_dead(data->philos[i]))
			ft_print_st("dead", &data->philos[i]);
		pthread_mutex_lock(&data->mtx_finished);
		finished = data->finished;
		pthread_mutex_unlock(&data->mtx_finished);
		if(data->lim_times_eaten != -1)
		{
			pthread_mutex_lock(&data->mtx_philo_full);
			full = data->philos_full;
			pthread_mutex_unlock(&data->mtx_philo_full);
			if(full == data->total_philo)
			{
				pthread_mutex_lock(&data->mtx_finished);
				data->finished = 1;
				pthread_mutex_unlock(&data->mtx_finished);
			}
		}
		i ++;
		if(i == data->total_philo)
			i = 0;
	}
}

void	ft_finish()
{

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
	pthread_mutex_init(&data->mtx_philo_full, NULL);
	pthread_mutex_init(&data->mtx_finished, NULL);
	pthread_mutex_init(&data->mtx_synchro, NULL);
	pthread_mutex_init(&data->mtx_write, NULL);
	pthread_mutex_lock(&data->mtx_synchro);
	data->philos_full = 0;
	data->finished = 0;
	data->philos = malloc(sizeof(t_philo) * data->total_philo);
	if(!data->philos)
		return (ft_error(2));
	data->threads = malloc(sizeof(pthread_t) * data->total_philo);
	if(!data->threads)
		return(ft_error(2));
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
	data.time_start = ft_get_time();
	pthread_mutex_unlock(&data.mtx_synchro);
	ft_status(&data);
	ft_finish();
	return(0);
}