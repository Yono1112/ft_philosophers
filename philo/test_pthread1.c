/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pthread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:10:14 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/13 15:06:07 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#define NUM 40
#define NUM_THREAD 2

typedef struct s_data
{
	int	start;
	int	num;
	int	*result;
}	t_data;

void	*func(void *arg)
{
	int		i;
	t_data	*pd;

	pd = (t_data *)arg;
	for (i = pd->start; i < pd->start + pd->num; i++)
	{
		pd->result[i] = i * i * i * i;
	}
	return (NULL);
}

int	main(void)
{
	int	i;
	int	r[NUM] = {0};
	pthread_t	t[NUM_THREAD];
	t_data	d[NUM_THREAD];
	int	ret;

	ret = 0;
	d[0].start = 0;
	d[0].num = NUM / 2;
	d[0].result = r;
	ret = pthread_create(&t[0], NULL, func, &d[0]);
	if (ret != 0)
		return (1);
	d[1].start = NUM / 2;
	d[1].num = NUM / 2;
	d[1].result = r;
	ret = pthread_create(&t[1], NULL, func, &d[1]);
	if (ret != 0)
		return (1);
	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	for (i = 0; i < NUM; i++)
	{
		printf("%d : %d\n", i , r[i]);
	}
	return (0);
}
