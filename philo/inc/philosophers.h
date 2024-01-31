/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 19:28:38 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/31 20:38:02 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

# define ARGS_ERROR "Wrong arguments. Try(numbers): \n- \
number_of_philosophers\n- time_to_die\n\
- time_to_eat\n- time_to_sleep\n\
- [number_of_times_each_philosopher_must_eat]\n"

# define INIT_ERROR "Error initializing the data"

struct s_data;

typedef struct s_philo
{
	int						philo;
	int						times_eaten;
	long					time_last_eat;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			right_fork;
	pthread_mutex_t			mtx_eat;
	struct s_data			*data;
}	t_philo;

typedef struct s_data
{
	long	total_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	lim_times_eaten;
	int		finished;
	int		philos_full;
	t_philo	*philos;
	long	time_start;
	pthread_t	*threads;
	pthread_mutex_t	mtx_data;
	pthread_mutex_t	mtx_write;
	pthread_mutex_t	mtx_finished;
	pthread_mutex_t	mtx_philo_full;

}	t_data;

int		ft_check_args(int argc, char **argv, t_data *data);
int		ft_error(int code);
long	ft_get_time(long time_start);
void	ft_print_st(char *str, t_philo *philo);
void	ft_routine_single(t_philo *philo);
void	*ft_routine(void *arg);
int		ft_init_philos(t_data *data);
int		ft_init_data(t_data *data);
int		ft_init_threads(t_data *data);
void	ft_usleep(long long time);
int		ft_is_dead(t_philo philo);
void	ft_routine_multiple(t_philo *philo, long time_eat, long time_sleep);
void	ft_status(t_data *data);
int		ft_are_full(t_data *data);
#endif