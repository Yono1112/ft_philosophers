/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 01:30:11 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/14 17:14:14 by yumaohno         ###   ########.fr       */
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
			philo->mtx_right_fork = &data->mtx_fork[(i + 1)];
		else
			philo->mtx_right_fork = &data->mtx_fork[i];
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

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->mtx_fork[i], NULL);
		data->philo[i].id = i + 1;
		data->philo[i].num_eaten = 0;
		assign_left_fork(&data->philo[i], data, i);
		assign_right_fork(&data->philo[i], data, i);
		i++;
	}
}
