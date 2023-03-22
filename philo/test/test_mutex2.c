/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mutex2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 03:37:56 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/14 04:05:40 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define PHILO 5
#define DISH 100

pthread_mutex_t	forks[PHILO];

void	swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	think(void)
{
	usleep(rand() % 100);
}

void	eat(int p_id)
{
	printf("Philosopher[%d] is eating.\n", p_id);
	usleep(rand() % 100);
}

void	get_forks(int right_fork, int left_fork, int p_id)
{
	pthread_mutex_lock(&(forks[right_fork]));
	pthread_mutex_lock(&(forks[left_fork]));
	printf("Philosopher[%d] has gotten forks.\n", p_id);
}

void	release_forks(int right_fork, int left_fork, int p_id)
{
	pthread_mutex_unlock(&(forks[right_fork]));
	pthread_mutex_unlock(&(forks[left_fork]));
	printf("Philosopher[%d] has released forks.\n", p_id);
}

void	*philosopher(void *arg)
{
	int	p_id;
	int	right_fork;
	int	left_fork;

	p_id = *(int *)arg;
	right_fork = p_id;
	left_fork = (right_fork + 1) % PHILO;
	if (p_id == PHILO - 1)
		swap(&right_fork, &left_fork);
	for (int i = 0; i < DISH; i++){
		think();
		get_forks(right_fork, left_fork, p_id);
		eat(p_id);
		release_forks(right_fork, left_fork, p_id);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread[PHILO];
	int			p_id[PHILO];

	for (int i = 0; i < PHILO; i++){
		pthread_mutex_init(&(forks[i]), NULL);
	}
	for (int i = 0; i < PHILO; i++){
		p_id[i] = i;
		pthread_create(&thread[i], NULL, *philosopher, (void *)&(p_id[i]));
	}
	for (int i = 0; i < PHILO; i++){
		pthread_join(thread[i], NULL);
	}
}
