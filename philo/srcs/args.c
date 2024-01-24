/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:36:25 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/24 01:44:13 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"
long	ft_atoi(const char *str)
{
	int		i;
	int		minus;
	long	res;

	i = 0;
	minus = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * minus);
}

int	ft_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_args(int argc, char **argv, t_data *data)
{
	int	i;

	i = 1;
	if(argc < 5 ||  argc > 6)
		return(ft_error(1));
	while(i < argc)
	{
		if(!ft_is_digit(argv[i]) ||  ft_atoi(argv[i]) == 0)
			return(ft_error(1));
		if (i == 1)
			data->total_philo = ft_atoi(argv[i]);
		else if(i == 2)
			data->time_to_die = ft_atoi(argv[i]);
		else if(i == 3)
			data->time_to_eat = ft_atoi(argv[i]);
		else if(i == 4)
			data->time_to_sleep = ft_atoi(argv[i]);
		i++;
	}
	if(argc == 6)
		data->lim_times_eaten = ft_atoi(argv[5]);
	else
		data->lim_times_eaten = -1;
	return(1);	
}
