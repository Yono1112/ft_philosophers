/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:35:56 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/07 19:12:39 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

#define NUM_THREAD 4
#define ADD_NUM 100000

long long sum = 0;

pthread_mutex_t mutex;

typedef struct thread_data
{
	int	addNum;
}	t_data;

void	*add(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	for (i = 0; i < data->addNum; i++){
		pthread_mutex_lock(&mutex);
		sum = sum + 1;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread[NUM_THREAD];
	t_data		data[NUM_THREAD];
	int			i;

	pthread_mutex_init(&mutex, NULL);
	for(i = 0; i < NUM_THREAD; i++){
		data[i].addNum = ADD_NUM / NUM_THREAD;
	}
	for(i = 0; i < NUM_THREAD; i++){
		pthread_create(&thread[i], NULL, add, &data[i]);
	}
	for(i = 0; i < NUM_THREAD; i++){
		pthread_join(thread[i], NULL);
	}
	pthread_mutex_destroy(&mutex);
	printf("sum = %lld\n", sum);
	return (0);
}
