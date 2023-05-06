/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 22:30:28 by yumaohno          #+#    #+#             */
/*   Updated: 2023/05/06 14:06:56 by yumaohno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_overflow(char c, int sign, long result)
{
	if (sign == 1 && (result > LONG_MAX / 10 || (result == LONG_MAX / 10
				&& c - '0' > LONG_MAX % 10)))
		return (1);
	if (sign == -1 && (result > LONG_MAX / 10 || (result == LONG_MAX / 10
				&& c - '0' > LONG_MAX % 10 + 1)))
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	result;
	int		i;

	i = 0;
	sign = 1;
	result = 0;
	while ((('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		if (sign == 1 && check_overflow(str[i], sign, result))
			return (LONG_MAX);
		if (sign == -1 && check_overflow(str[i], sign, result))
			return (LONG_MIN);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static void	parse_args(t_data *data, int argc, char **argv)
{
	data->philo_num = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
	{
		data->is_must_eat_num = true;
		data->must_eat_num = ft_atol(argv[5]);
	}
	else
	{
		data->is_must_eat_num = false;
		data->must_eat_num = 0;
	}
}

static bool	check_num(int argc, char **argv)
{
	int		i;
	int		j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || '9' < argv[i][j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_args(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (false);
	if (!check_num(argc, argv))
		return (false);
	parse_args(data, argc, argv);
	if (data->philo_num < 1 || data->philo_num > 200
		|| data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1 || data->must_eat_num < 0)
		return (false);
	return (true);
}

// static int	ft_check_overflow(long num, char const *str, int sign)
// {
// 	long	check_div;
// 	long	check_mod;

// 	check_div = LONG_MAX / 10;
// 	check_mod = LONG_MAX % 10;
// 	if (num > check_div || (num >= check_div && (*str - '0') > check_mod))
// 	{
// 		if (sign == 1)
// 			return (1);
// 		else if (sign == -1 && *str > (check_mod + 1))
// 			return (-1);
// 	}
// 	return (0);
// }

// static int	ft_atoi(const char *str)
// {
// 	int		i;
// 	int		flag;
// 	long	result;

// 	i = 0;
// 	flag = 1;
// 	result = 0;
// 	while ((('\t' <= str[i] && str[i] <= '\r') || str[i] == ' ') && str[i])
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			flag *= -1;
// 		i++;
// 	}
// 	while (('0' <= str[i] && str[i] <= '9') && str[i])
// 	{
// 		if (ft_check_overflow(result, &str[i], flag) == 1)
// 			return ((int)(LONG_MAX));
// 		else if (ft_check_overflow(result, &str[i], flag) == -1)
// 			return ((int)(LONG_MIN));
// 		result = result * 10 + (str[i] - '0');
// 		i++;
// 	}
// 	return (result * flag);
// }
