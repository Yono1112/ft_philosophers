/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:44:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/21 18:37:31 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eat_timestamp_and_wait(t_philo *philo)
{
	time_t	current_time;

	current_time = get_time();
	if (!current_time)
		return (1);
	pthread_mutex_lock(&philo->data->mtx_philo[philo->index]);
	philo->last_eat_time = current_time;
	pthread_mutex_unlock(&philo->data->mtx_philo[philo->index]);
	while (philo->data->time_to_eat > get_time() - current_time)
		usleep(100);
	return (0);
}

static int	eat_countnum(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mtx_philo[philo->index]);
	philo->num_eaten++;
	pthread_mutex_unlock(&philo->data->mtx_philo[philo->index]);
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (lock_forks(philo))
		return (1);
	if (print_message(philo, "is eating"))
	{
		unlock_forks(philo);
		return (1);
	}
	if (eat_timestamp_and_wait(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	if (eat_countnum(philo))
	{
		unlock_forks(philo);
		return (1);
	}
	unlock_forks(philo);
	return (0);
}
