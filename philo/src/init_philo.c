/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:30:11 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/18 17:00:26 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	assign_right_fork(t_philo *philo, t_data *data, int i)
{
	if (i == data->philo_num - 1)
	{
		if (i % 2 == 0)
			philo->mtx_right_fork = &data->mtx_fork[i];
		else
			philo->mtx_right_fork = &data->mtx_fork[0];
	}
	else
	{
		if (i % 2 == 0)
			philo->mtx_right_fork = &data->mtx_fork[i];
		else
			philo->mtx_right_fork = &data->mtx_fork[i + 1];
	}
}

static void	assign_left_fork(t_philo *philo, t_data *data, int i)
{
	if (i == data->philo_num - 1)
	{
		if (i % 2 == 0)
			philo->mtx_left_fork = &data->mtx_fork[0];
		else
			philo->mtx_left_fork = &data->mtx_fork[i];
	}
	else
	{
		if (i % 2 == 0)
			philo->mtx_left_fork = &data->mtx_fork[i + 1];
		else
			philo->mtx_left_fork = &data->mtx_fork[i];
	}
}

int	init_philo(t_data *data)
{
	int	i;

	printf("start init_philo\n");
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_mutex_init(&data->mtx_fork[i], NULL))
			return (1);
		data->philo[i].id = i + 1;
		data->philo[i].index = i;
		data->philo[i].num_eaten = 0;
		data->philo[i].data = data;
		assign_left_fork(&data->philo[i], data, i);
		assign_right_fork(&data->philo[i], data, i);
		i++;
	}
	if (pthread_mutex_init(&data->mtx_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->mtx_stop, NULL))
		return (1);
	printf("end init_philo\n");
	return (0);
}
