/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:56:46 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/07 18:04:28 by yumaohno         ###   ########.fr       */
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
# define RET_ERROR 1
# define RET_SUCCESS 0
# define MESSAGE_EAT "is eating"
# define MESSAGE_SLEEP "is sleeping"
# define MESSAGE_THINK "is thinking"
# define MESSAGE_FORK "has taken a fork"
# define MESSAGE_DIE "died"

typedef struct s_philo
{
	struct s_data	*data;
	long			id;
	long			index;
	long			num_eaten;
	time_t			last_eat_time;
	pthread_t		philo_thread;
	pthread_mutex_t	*mtx_right_fork;
	pthread_mutex_t	*mtx_left_fork;
}	t_philo;

typedef struct s_data
{
	long			philo_num;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	long			must_eat_num;
	bool			is_must_eat_num;
	time_t			start_time;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	mtx_philo[MAX_PHILO];
	pthread_mutex_t	mtx_fork[MAX_PHILO];
	pthread_mutex_t	mtx_print;
	bool			is_stop;
	pthread_mutex_t	mtx_is_stop;
	pthread_t		monitor_thread;
}	t_data;

bool	check_args(int argc, char **argv, t_data *data);
int		init_philo(t_data *data);
int		philo_thread(t_data *data);
void	*philo_func(void *arg);
int		philo_eat(t_philo *philo);
int		lock_forks(t_philo	*philo);
int		unlock_forks(t_philo *philo, int ret_flag);
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);
int		print_message(t_philo *philo, char *message);
time_t	get_time(void);
void	*monitor_func(void *arg);
int		destroy_thread(t_data *data);

#endif