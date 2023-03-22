/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pthread2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:12:46 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/14 00:03:29 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static void	f1(void)
{
	int i;

	for (i = 0; i < 8; i++)
	{
		printf("Doing one thing\n");
		usleep(3);
	}
}

static void	f2(void)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		printf("Doing another\n");
		usleep(2);
	}
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	int			ret1;
	int			ret2;

	ret1 = pthread_create(&thread1, NULL, (void *)f1, NULL);
	ret2 = pthread_create(&thread1, NULL, (void *)f2, NULL);
	if (ret1 != 0 || ret2 != 0)
	{
		printf("Error : pthread_create");
		return (1);
	}
	printf("execute pthread_join thread1\n");
	ret1 = pthread_join(thread1, NULL);
	if (ret1 != 0)
	{
		printf("Error : pthread_join ret1 = %d\n", ret1);
		return (1);
	}
	printf("execute pthread_join thread2\n");
	ret2 = pthread_join(thread2, NULL);
	if (ret2 != 0)
	{
		printf("Error : pthread_join ret2 = %d\n", ret2);
		return (1);
	}
	printf("done\n");
	return (0);
}
