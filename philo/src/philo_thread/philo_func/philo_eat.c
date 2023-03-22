/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:44:58 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/22 07:32:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eat_timestamp_and_wait(t_philo *philo)
{
	time_t	current_time;

	current_time = get_time();
	if (!current_time)
		return (RET_ERROR);
	pthread_mutex_lock(&philo->data->mtx_philo[philo->index]);
	philo->last_eat_time = current_time;
	pthread_mutex_unlock(&philo->data->mtx_philo[philo->index]);
	while (philo->data->time_to_eat > get_time() - current_time)
		usleep(100);
	return (RET_SUCCESS);
}

static int	eat_countnum(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mtx_philo[philo->index]);
	philo->num_eaten++;
	pthread_mutex_unlock(&philo->data->mtx_philo[philo->index]);
	return (RET_SUCCESS);
}

int	philo_eat(t_philo *philo)
{
	if (lock_forks(philo))
		return (RET_ERROR);
	if (print_message(philo, "is eating"))
		return (unlock_forks(philo, RET_ERROR));
	if (eat_timestamp_and_wait(philo))
		return (unlock_forks(philo, RET_ERROR));
	if (eat_countnum(philo))
		return (unlock_forks(philo, RET_ERROR));
	unlock_forks(philo, RET_SUCCESS);
	return (RET_SUCCESS);
}
