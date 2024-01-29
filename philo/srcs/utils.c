/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 02:05:38 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/29 04:11:31 by tfiguero         ###   ########.fr       */
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


// void	ft_print_st(char *s, t_philo *aux )
// {
// 	long		i;
// 	int		game_finished;

// 	i = ft_get_time() - (aux->data->time_start + aux->time_last_eat);
// 	pthread_mutex_lock(&aux->data->mtx_write);
// 	pthread_mutex_lock(&aux->data->mtx_finished);
// 	game_finished = aux->data->finished;
// 	if (game_finished != 1)
// 		printf("%ld %d %s\n", i, aux->philo + 1, s);
// 	
// 	pthread_mutex_unlock(&aux->data->mtx_finished);
// 	pthread_mutex_unlock(&aux->data->mtx_write);
// }
void	ft_print_st(char *str, t_philo *philo)
{
	long	time;
	int		finished;

	pthread_mutex_lock(&philo->data->mtx_write);
	pthread_mutex_lock(&philo->data->mtx_finished);
	finished = philo->data->finished;
	time = ft_get_time() - philo->data->time_start; 
	if(finished == 0)
		printf("%li:::Philo %i is %s\n", time, philo->philo, str);
	if(!ft_strcmp(str, "dead"))
  		philo->data->finished = 1;
	pthread_mutex_unlock(&philo->data->mtx_write);
	pthread_mutex_unlock(&philo->data->mtx_finished);
}
int	ft_is_dead(t_philo philo)
{
	long	time_now;
	long	time_diff;


	time_now = ft_get_time() - philo.data->time_start;
	pthread_mutex_lock(&philo.mtx_eat);
	time_diff = time_now - philo.time_last_eat;
	pthread_mutex_unlock(&philo.mtx_eat);
	if(time_diff > philo.data->time_to_die)
		return(1);
	return(0);
}

long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"));
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time)
{
	time += ft_get_time();
	while (ft_get_time() <= time)
		usleep(200);
}