/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:45:49 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/22 07:34:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->mtx_print);
	pthread_mutex_lock(&philo->data->mtx_stop);
	if (philo->data->stop == true)
	{
		pthread_mutex_unlock(&philo->data->mtx_stop);
		pthread_mutex_unlock(&philo->data->mtx_print);
		return (RET_ERROR);
	}
	pthread_mutex_unlock(&philo->data->mtx_stop);
	printf("%ld %d %s\n", get_time() - philo->data->start_time,
		philo->id, message);
	pthread_mutex_unlock(&philo->data->mtx_print);
	return (RET_SUCCESS);
}
