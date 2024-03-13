/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:48 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 14:30:25 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->philos_count * sizeof(pthread_mutex_t));
	data->status_mutex = malloc(data->philos_count * sizeof(pthread_mutex_t));
	if (!data->forks || !data->status_mutex)
		return (ft_error_free(MALLOC_FAILED, data));
	while (i < data->philos_count)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0
			|| pthread_mutex_init(&(data->status_mutex[i]), NULL) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&(data->forks[i]));
				pthread_mutex_destroy(&(data->status_mutex[i]));
				i--;
			}
			return (ft_error_free(MUTEX_INIT_FAILED, data));
		}
		i++;
	}
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(data->philos_count * sizeof(t_philo));
	if (!(data->philos))
		return (ft_error_clear_mutex(MALLOC_FAILED, data));
	while (i < data->philos_count)
	{
		data->philos[i].data = &data;
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_count = 0;
		data->philos[i].fork_r = &(data->forks[i]);
		data->philos[i].fork_l = &(data->forks[(i + 1) % data->philos_count]);
		data->philos[i].status_mutex = &(data->status_mutex[i]);
		data->philos[i].status = THINKING;
		data->philos[i].is_running = 1;
		i++;
	}
	return (0);
}
