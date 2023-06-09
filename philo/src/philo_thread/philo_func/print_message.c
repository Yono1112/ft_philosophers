/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:45:49 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/06 14:06:01 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->mtx_print);
	pthread_mutex_lock(&philo->data->mtx_is_stop);
	if (philo->data->is_stop == true)
	{
		pthread_mutex_unlock(&philo->data->mtx_is_stop);
		pthread_mutex_unlock(&philo->data->mtx_print);
		return (RET_ERROR);
	}
	pthread_mutex_unlock(&philo->data->mtx_is_stop);
	printf("%ld %ld %s\n", get_time() - philo->data->start_time,
		philo->id, message);
	pthread_mutex_unlock(&philo->data->mtx_print);
	return (RET_SUCCESS);
}
