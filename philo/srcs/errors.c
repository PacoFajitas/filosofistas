/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:43:41 by tfiguero          #+#    #+#             */
/*   Updated: 2024/01/31 20:58:37 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	ft_error(int code)
{
	if(code == 1)
		write(2, ARGS_ERROR, 147);
	else if(code == 2)
		write(2, INIT_ERROR, 27);
	else if(code == 3)
		write(2, "Error creating/joining thread\n", 30);
	return(0);
}