/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:16:42 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/16 02:24:09 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	*philo_action(void *arg)
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

// time_t	get_time(void)
// {
// 	struct timeval	tv;
// 	time_t			time;

// 	gettimeofday(&tv, NULL);
// 	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
// 	return (time);
// }

// int		philo_eat(t_philo *philo)
// {
// }

void	*philosopher_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (philo->data->stop == 1)
			return (NULL);
		if (!philo_eat(philo))
			return (NULL);
		if (!philo_sleep(philo))
			return (NULL);
		if (!philo_think(philo))
			return (NULL);
	}
}

int	create_thread(t_data *data)
{
	int		i;

	i = 0;
	printf("start create_thread\n");
	printf("%d\n", data->philo_num);
	while (i < data->philo_num)
	{
		pthread_create(&data->philo[i].thread,
			NULL, philosopher_func, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	printf("end create_thread\n");
	return (0);
}
