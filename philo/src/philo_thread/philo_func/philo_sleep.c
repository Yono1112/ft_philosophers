/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 03:45:37 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/04 23:00:46 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_sleep(t_philo *philo)
{
	time_t	current_time;

	if (print_message(philo, MESSAGE_SLEEP))
		return (RET_ERROR);
	current_time = get_time();
	if (!current_time)
		return (RET_ERROR);
	while (philo->data->time_to_sleep > get_time() - current_time)
		usleep(100);
	return (RET_SUCCESS);
}
