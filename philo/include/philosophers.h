/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:56:46 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/21 18:42:26 by yumaohno         ###   ########.fr       */
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

typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				index;
	int				num_eaten;
	time_t			last_eat_time;
	pthread_t		philo_thread;
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
	bool			is_must_eat_num;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	mtx_fork[MAX_PHILO];
	pthread_mutex_t	mtx_philo[MAX_PHILO];
	time_t			start_time;
	bool			stop;
	pthread_mutex_t	mtx_stop;
	pthread_mutex_t	mtx_print;
	pthread_t		monitor_thread;
}	t_data;

bool	check_args(int argc, char **argv, t_data *data);
int		init_philo(t_data *data);
int		create_thread(t_data *data);
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