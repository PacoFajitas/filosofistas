/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 21:58:31 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/29 08:38:49 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_routine_multiple(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print_st("picking the left fork", philo);
	pthread_mutex_lock(&philo->right_fork);
	ft_print_st("picking the right fork", philo);
	pthread_mutex_lock(&philo->mtx_eat);
	ft_print_st("eating", philo);
	ft_usleep(philo->data->time_to_eat);
	philo->time_last_eat = ft_get_time() - philo->data->time_start;
	pthread_mutex_unlock(&philo->mtx_eat);
	if(philo->data->lim_times_eaten > 0)
	{
		philo->times_eaten++;
		if(philo->times_eaten == philo->data->lim_times_eaten)
		{
			pthread_mutex_lock(&philo->data->mtx_philo_full);
			philo->data->lim_times_eaten++;
			pthread_mutex_unlock(&philo->data->mtx_philo_full);
		}
	}	
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
	ft_print_st("sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
	ft_print_st("thinking", philo);
}
void	*ft_routine(void *arg)
{
	t_philo *philo;
	int		finished;
	long	time_eat;
	
	philo = arg;
	finished = 0;
	time_eat = 0;
	pthread_mutex_lock(&philo->data->mtx_synchro);
	pthread_mutex_unlock(&philo->data->mtx_synchro);
	if (philo->philo % 2 == 0)
		usleep(philo->data->time_to_eat * 100);
	while(finished == 0)
	{
		ft_routine_multiple(philo);
		pthread_mutex_lock(&philo->data->mtx_finished);
		finished = philo->data->finished;
		pthread_mutex_unlock(&philo->data->mtx_finished);
	}
	return((void *) 0);
}