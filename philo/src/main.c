/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:54:09 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/14 16:53:19 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!check_args(argc, argv, &data))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	printf("philo_num: %d, time_to_die: %ld, time_to_eat: %ld, time_to_sleep: %ld, must_eat: %d\n", data.philo_num, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.must_eat_num);
	init_philo(&data);
	// i = 0;
	// while (i < data.philo_num)
	// {
	// 	pthread_create(&data.philo[i].thread, NULL, philo_f, &data.philo[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < data.philo_num)
	// {
	// 	pthread_join(data.philo[i].thread, NULL);
	// 	i++;
	// }
	return (0);
}
