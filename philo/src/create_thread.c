/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:16:42 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/19 03:55:14 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	*philo_action(t_philo *arg)
// {
// 	t_philo	*philo;
// 	int		i;

// 	i = 0;
// 	philo = (t_philo *)arg;
// 	printf("philo : %d\n", philo->data->philo_num);
// 	while (i < 10)
// 	{
// 		printf("Hello philosopher[%d]\n", philo->id);
// 		i++;
// 	}
// 	return (NULL);
// }

time_t	get_time(void)
{
	struct timeval	tv;
	time_t			time;

	if (gettimeofday(&tv, NULL))
		return (0);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->mtx_print);
	pthread_mutex_lock(&philo->data->mtx_stop);
	if (philo->data->stop == true)
	{
		pthread_mutex_unlock(&philo->data->mtx_stop);
		pthread_mutex_unlock(&philo->data->mtx_print);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mtx_stop);
	printf("%ld %d %s\n", get_time() - philo->data->start_time,
		philo->id, message);
	pthread_mutex_unlock(&philo->data->mtx_print);
	return (0);
}

void	*philo_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->data->start_time = get_time();
	philo->last_eat_time = get_time();
	if (!philo->data->start_time || !philo->last_eat_time)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		if (philo_think(philo))
			break ;
	}
	return (NULL);
}

int	create_thread(t_data *data)
{
	int		i;

	i = 0;
	printf("start create_thread\n");
	printf("%d\n", data->philo_num);
	while (i < data->philo_num)
	{
		pthread_create(&data->philo[i].philo_thread,
			NULL, philo_func, &data->philo[i]);
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, monitor_func, data);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i].philo_thread, NULL);
		i++;
	}
	printf("end create_thread\n");
	return (0);
}
