/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:16:42 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/19 03:14:29 by yumaohno         ###   ########.fr       */
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

int	eat_timestamp(t_philo *philo)
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

int eat_countnum(t_philo *philo)
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
	if (eat_timestamp(philo))
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

int	philo_sleep(t_philo *philo)
{
	time_t	current_time;

	if (print_message(philo, "is sleeping"))
		return (1);
	current_time = get_time();
	if (!current_time)
		return (1);
	while (philo->data->time_to_sleep > get_time() - current_time)
		usleep(100);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (print_message(philo, "is thinking"))
		return (1);
	usleep(100);
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
		pthread_create(&data->philo[i].thread,
			NULL, philo_func, &data->philo[i]);
		i++;
	}
	pthread_create(&data->monitor_thread, NULL, monitor_func, data);
	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	printf("end create_thread\n");
	return (0);
}
