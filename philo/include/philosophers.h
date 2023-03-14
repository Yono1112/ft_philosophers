/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:56:46 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/14 14:38:59 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# define MAX_PHILO 200

typedef struct s_philo
{
	int				id;
	int				num_eaten;
	pthread_t		thread[MAX_PHILO];
	pthread_mutex_t	*mtx_right_fork;
	pthread_mutex_t	*mtx_left_fork;
}	t_philo;

typedef struct s_data
{
	int				philo_num;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_num;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	mtx_fork[MAX_PHILO];
	pthread_mutex_t	mtx_stop;
	bool			stop;
}	t_data;

bool	check_args(int argc, char **argv, t_data *data);
#endif