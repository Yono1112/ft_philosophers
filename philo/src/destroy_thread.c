/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:28:25 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/19 14:45:39 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_thread(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&data->mtx_print))
		return (1);
	if (pthread_mutex_destroy(&data->mtx_stop))
		return (1);
	while (i < data->philo_num)
	{
		if (pthread_mutex_destroy(&data->mtx_fork[i]))
			return (1);
		if (pthread_mutex_destroy(&data->mtx_philo[i]))
			return (1);
		i++;
	}
	return (0);
}
