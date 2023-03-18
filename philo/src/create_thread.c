/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:16:42 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/18 17:03:54 by yumaohno         ###   ########.fr       */
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

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

int	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->mtx_print);
	pthread_mutex_lock(&philo->data->mtx_stop);
	if (philo->data->stop == 1)
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
	print_message(philo, "has released forks");
}

int	philo_eat(t_philo *philo)
{
	if (lock_forks(philo))
		return (1);
	philo->last_eat_time = get_time();
	philo->num_eaten++;
	if (philo->num_eaten == philo->data->must_eat_num)
		philo->data->stop = 1;
	if (print_message(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->mtx_right_fork);
		pthread_mutex_unlock(philo->mtx_left_fork);
		return (1);
	}
	usleep(philo->data->time_to_eat * 1000);
	unlock_forks(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (print_message(philo, "is sleeping"))
		return (1);
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (print_message(philo, "is thinking"))
		return (1);
	return (0);
}

void	*philo_func(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		if (philo->data->stop == 1)
			break ;
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
		pthread_create(&data->philo[i].thread,
			NULL, philo_func, &data->philo[i]);
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
