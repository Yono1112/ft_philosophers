/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:47:08 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/19 03:47:23 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_forks(t_philo	*philo)
{
	pthread_mutex_lock(philo->mtx_right_fork);
	if (print_message(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->mtx_right_fork);
		return (1);
	}
	pthread_mutex_lock(philo->mtx_left_fork);
	if (print_message(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->mtx_right_fork);
		pthread_mutex_unlock(philo->mtx_left_fork);
		return (1);
	}
	return (0);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->mtx_right_fork);
	pthread_mutex_unlock(philo->mtx_left_fork);
	// print_message(philo, "has released forks");
}
