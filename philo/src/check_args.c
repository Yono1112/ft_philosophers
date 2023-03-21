/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 22:30:28 by yumaohno          #+#    #+#             */
/*   Updated: 2023/03/21 18:28:02 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_check_overflow(long num, char const *str, int sign)
{
	long	check_div;
	long	check_mod;

	check_div = LONG_MAX / 10;
	check_mod = LONG_MAX % 10;
	if (num > check_div || (num >= check_div && (*str - '0') > check_mod))
	{
		if (sign == 1)
			return (1);
		else if (sign == -1 && *str > (check_mod + 1))
			return (-1);
	}
	return (0);
}

static int	ft_atoi(const char *str)
{
	int		i;
	int		flag;
	long	result;

	i = 0;
	flag = 1;
	result = 0;
	while ((('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag *= -1;
		i++;
	}
	while (('0' <= str[i] && str[i] <= '9') && str[i])
	{
		if (ft_check_overflow(result, &str[i], flag) == 1)
			return ((int)(LONG_MAX));
		else if (ft_check_overflow(result, &str[i], flag) == -1)
			return ((int)(LONG_MIN));
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * flag);
}

bool	check_args(int argc, char **argv, t_data *data)
{
	int		i;
	int		j;

	if (argc != 5 && argc != 6)
		return (false);
	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (false);
			j++;
		}
		i++;
	}
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->is_must_eat_num = true;
		data->must_eat_num = ft_atoi(argv[5]);
	}
	else
	{
		data->is_must_eat_num = false;
		data->must_eat_num = -1;
	}
	if (data->philo_num < 1 || data->philo_num > 200
		|| data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || data->must_eat_num == 0)
		return (false);
	return (true);
}
