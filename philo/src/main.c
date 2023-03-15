/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:54:09 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/15 20:49:38 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	ret = 0;
	if (!check_args(argc, argv, &data))
		return (1);
	printf("philo_num: %d, time_to_die: %ld, time_to_eat: %ld, time_to_sleep: %ld, must_eat: %d\n", data.philo_num, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.must_eat_num);
	ret = init_philo(&data);
	if (ret)
		return (1);
	ret = create_thread(&data);
	if (ret)
		return (1);
	return (0);
}
