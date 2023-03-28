/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:54:09 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/28 15:51:49 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!check_args(argc, argv, &data))
		return (RET_ERROR);
	// printf("philo_num: %d, time_to_die: %ld, time_to_eat: %ld, time_to_sleep: %ld, must_eat: %d\n", data.philo_num, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.must_eat_num);
	if (init_philo(&data))
		return (RET_ERROR);
	if (philo_thread(&data))
		return (RET_ERROR);
	if (destroy_thread(&data))
		return (RET_ERROR);
	return (RET_SUCCESS);
}
