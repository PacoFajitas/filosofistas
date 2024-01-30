/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:05:38 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/30 22:20:00 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_strcmp(char *ehe, char *cmp)
{
	int	i;

	i = 0;
	while(ehe[i] && cmp[i])
	{
		if(ehe[i] != cmp[i])
			return(1);
		i++;
	}
	if((ehe[i] && !cmp[i]) || (cmp[i] && !ehe[i]))
		return(1);
	return(0);
}


void	ft_print_st(char *str, t_philo *philo)
{
	long	time;
	int		finished;

	pthread_mutex_lock(&philo->data->mtx_finished);
	finished = philo->data->finished;
	pthread_mutex_unlock(&philo->data->mtx_finished);
	pthread_mutex_lock(&philo->data->mtx_write);
	time = ft_get_time(philo->data->time_start); 
	if( finished == 0)
		printf("%li:::Philo %i is %s\n", time, philo->philo, str);
	pthread_mutex_unlock(&philo->data->mtx_write);
}

long	ft_get_time(long time_start)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000) - time_start);
}

void	ft_usleep(long long time)
{
	time += ft_get_time(0);
	while (ft_get_time(0) <= time)
		usleep(200);
}