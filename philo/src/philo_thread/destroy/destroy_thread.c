/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:28:25 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/21 19:09:51 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_thread(t_data *data)
{
	int	i;

	if (pthread_mutex_destroy(&data->mtx_print))
		return (RET_ERROR);
	if (pthread_mutex_destroy(&data->mtx_stop))
		return (RET_ERROR);
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_destroy(&data->mtx_fork[i]))
			return (RET_ERROR);
		if (pthread_mutex_destroy(&data->mtx_philo[i]))
			return (RET_ERROR);
		i++;
	}
	return (RET_SUCCESS);
}
