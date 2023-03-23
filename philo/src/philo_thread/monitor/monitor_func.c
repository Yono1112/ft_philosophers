/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:10:52 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/23 12:26:34 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_death(t_data *data)
{
	int		i;
	time_t	current_time;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->mtx_philo[i]);
		current_time = get_time();
		if (current_time - data->philo[i].last_eat_time > data->time_to_die)
		{
			pthread_mutex_lock(&data->mtx_print);
			printf("%ld %d died\n", current_time - data->start_time, i + 1);
			pthread_mutex_unlock(&data->mtx_print);
			pthread_mutex_unlock(&data->mtx_philo[i]);
			return (true);
		}
		pthread_mutex_unlock(&data->mtx_philo[i]);
		i++;
	}
	return (false);
}

static bool	check_eat_num(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->mtx_philo[i]);
		if (data->philo[i].num_eaten < data->must_eat_num)
		{
			pthread_mutex_unlock(&data->mtx_philo[i]);
			return (false);
		}
		pthread_mutex_unlock(&data->mtx_philo[i]);
		i++;
	}
	pthread_mutex_lock(&data->mtx_print);
	// printf("All philosophers have eaten %d times\n", data->must_eat_num);
	pthread_mutex_unlock(&data->mtx_print);
	return (true);
}

void	*monitor_func(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	usleep(data->time_to_die / 2);
	while (1)
	{
		if (check_death(data))
		{
			pthread_mutex_lock(&data->mtx_is_stop);
			data->is_stop = true;
			pthread_mutex_unlock(&data->mtx_is_stop);
			break ;
		}
		if (data->is_must_eat_num == true)
		{
			if (check_eat_num(data))
			{
				pthread_mutex_lock(&data->mtx_is_stop);
				data->is_stop = true;
				pthread_mutex_unlock(&data->mtx_is_stop);
				break ;
			}
		}
	}
	return (NULL);
}
