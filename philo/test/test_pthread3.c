/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pthread3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:38:49 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/13 10:48:00by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

long long num = 0;

void	*output(void *arg)
{
	for (;;)
	{
		if (num == -1)
		{
			printf("num = -1 finished!\n");
			break;
		}
		printf("num = %lld\n", num);
	}
	return (NULL);
}

void	*input(void *arg)
{
	for (;;)
	{
		scanf("%lld", &num);
		if (num == -1)
			break;
	}
	return (NULL);
}

int main(void)
{
	pthread_t	output_thread;
	pthread_t	input_thread;

	pthread_create(&output_thread, NULL, output, NULL);
	pthread_create(&input_thread, NULL, input, NULL);
	pthread_join(output_thread, NULL);
	pthread_join(input_thread, NULL);
	return (0);
}
