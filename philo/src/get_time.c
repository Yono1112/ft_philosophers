/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:23:44 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/21 15:24:04 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time(void)
{
	struct timeval	tv;
	time_t			time;

	if (gettimeofday(&tv, NULL))
		return (0);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
