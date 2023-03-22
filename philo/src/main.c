/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:54:09 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/22 17:08:39 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, argv, &data))
		return (1);
	// printf("philo_num: %d, time_to_die: %ld, time_to_eat: %ld, time_to_sleep: %ld, must_eat: %d\n", data.philo_num, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.must_eat_num);
	if (init_philo(&data))
		return (1);
	if (create_thread(&data))
		return (1);
	if (destroy_thread(&data))
		return (1);
	return (0);
}
