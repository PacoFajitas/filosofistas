/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:05:38 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/24 02:54:59 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	ft_print_st(char *str, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->data->mtx_write);
	pthread_mutex_lock(&philo->data->mtx_finished);
	time = ft_get_time() - philo->data->time_start; 
	if(philo->data->finished == 0)
		printf("%li:::Philo %i has %s", time, philo->philo, str);
	pthread_mutex_lock(&philo->data->mtx_finished);
	pthread_mutex_unlock(&philo->data->mtx_write);
}

long	ft_get_time(void)
{
	long 			ret;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ret = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return(ret);
}