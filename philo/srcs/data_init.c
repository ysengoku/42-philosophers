/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:48 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 11:44:28 by yusengok         ###   ########.fr       */
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
	{
		ft_free(data);
		return (ft_error(MALLOC_FAILED));
	}
	while (i < data->philos_count)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0 ||
			pthread_mutex_init(&(data->status_mutex[i]), NULL) != 0)
		{
			// need to destroy mutex before return
			ft_free(data);
			return (ft_error(MUTEX_INIT_FAILED));
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
	{
		// need to destroy mutex if exists before return
		ft_free(data);
		ft_error(MALLOC_FAILED);
	}
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
		pthread_create(&(data->philos[i].tid), NULL, start_routine, data);
		i++;
	}
	return (0);
}
