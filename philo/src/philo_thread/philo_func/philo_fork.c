/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:47:08 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/04 23:00:22 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_forks(t_philo	*philo)
{
	pthread_mutex_lock(philo->mtx_right_fork);
	if (print_message(philo, MESSAGE_FORK) || philo->data->philo_num == 1)
	{
		pthread_mutex_unlock(philo->mtx_right_fork);
		if (philo->data->philo_num == 1)
			usleep(philo->data->time_to_die * 1000 + 1000);
		return (RET_ERROR);
	}
	pthread_mutex_lock(philo->mtx_left_fork);
	if (print_message(philo, MESSAGE_FORK))
	{
		pthread_mutex_unlock(philo->mtx_right_fork);
		pthread_mutex_unlock(philo->mtx_left_fork);
		return (RET_ERROR);
	}
	return (RET_SUCCESS);
}

int	unlock_forks(t_philo *philo, int ret_flag)
{
	pthread_mutex_unlock(philo->mtx_right_fork);
	pthread_mutex_unlock(philo->mtx_left_fork);
	if (ret_flag == RET_ERROR)
		return (RET_ERROR);
	else
		return (RET_SUCCESS);
}
