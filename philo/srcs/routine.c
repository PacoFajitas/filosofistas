/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:58:31 by tfiguero          #+#    #+#             */
/*   Updated: 2024/02/03 16:29:21 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_routine_multiple(t_philo *philo, long time_eat, long time_sleep)
{
	pthread_mutex_lock(&philo->right_fork);
	ft_print_st("taking the right fork", philo);
	pthread_mutex_lock(philo->left_fork);
	ft_print_st("taking the left fork", philo);
	pthread_mutex_lock(&philo->mtx_eat);
	ft_print_st("eating", philo);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->lim_times_eaten)
	{
		pthread_mutex_lock(&philo->data->mtx_philo_full);
		philo->data->philos_full++;
		pthread_mutex_unlock(&philo->data->mtx_philo_full);
	}
	philo->time_last_eat = ft_get_time(philo->data->time_start);
	pthread_mutex_unlock(&philo->mtx_eat);
	ft_usleep(time_eat);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_print_st("sleeping", philo);
	ft_usleep(time_sleep);
	ft_print_st("thinking", philo);
}

void	*ft_routine(void *arg)
{
	t_philo *philo;
	int		finished;
	long	time_eat;
	long	time_sleep;
	
	philo = arg;
	finished = 0;
	pthread_mutex_lock(&philo->data->mtx_data);
	time_eat = philo->data->time_to_eat;
	time_sleep = philo->data->time_to_sleep;
	pthread_mutex_unlock(&philo->data->mtx_data);
	if (philo->philo % 2 == 0)
		ft_usleep(philo->data->time_to_eat/10);
	while(finished == 0)
	{
		if(philo->data->total_philo == 1)
		{
			pthread_mutex_lock(&philo->right_fork);
			ft_print_st("taking the right fork", philo);
			ft_usleep(philo->data->time_to_die);
			pthread_mutex_unlock(&philo->right_fork);
			break;
		}
		ft_routine_multiple(philo, time_eat, time_sleep);
		pthread_mutex_lock(&philo->data->mtx_finished);
		finished = philo->data->finished;
		pthread_mutex_unlock(&philo->data->mtx_finished);
	}
	return((void *) 0);
}