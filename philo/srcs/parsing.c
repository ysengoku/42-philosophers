/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:59:29 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/08 11:29:22 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_args(char **argv, t_data *data);
static int	ft_atoi_pos(char *arg);

int	check_arg(int argc, char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		return (ft_error(INVALID_ARGC));
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			while (argv[i][j] == ' ' || (argv[i][j] >= 9 && argv[i][j] <= 13))
				j++;
			if (argv[i][j] == '+')
				j++;
			if (argv[i][j] == '-')
				return (ft_error(NEGATIVE_NBR));
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (ft_error(INVALID_NBR));
			j++;
		}
		i++;
	}
	if (get_args(argv, data) == 1)
		return (ft_error(INVALID_NBR));
	return (0);
}

static int	get_args(char **argv, t_data *data)
{
	data->philos_count = ft_atoi_pos(argv[1]);
	if (data->philos_count == -1)
		return (1);
	data->time_to_die = ft_atoi_pos(argv[2]);
	if (data->time_to_die == -1)
		return (1);
	data->time_to_eat = ft_atoi_pos(argv[3]);
	if (data->time_to_eat == -1)
		return (1);
	data->time_to_sleep = ft_atoi_pos(argv[4]);
	if (data->time_to_sleep == -1)
		return (1);
	if (argv[5])
	{
		data->meal_to_must_eat = ft_atoi_pos(argv[5]);
		if (data->meal_to_must_eat == -1)
			return (1);
	}
	return (0);
}

static int	ft_atoi_pos(char *arg)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	if (arg[i] == '+')
		i++;
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		nbr += (arg[i] - '0');
		if (arg[i + 1] >= '0' && arg[i + 1] <= '9')
			nbr *= 10;
		else if (nbr > LONG_MAX / 10
			|| (nbr == LONG_MAX / 10 && arg[i] - '0' > 7))
			return (-1);
		i++;
	}
	return ((int)nbr);
}
