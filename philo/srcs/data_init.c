/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:48 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/12 15:10:13 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->philos_count * sizeof(pthread_mutex_t));
	data->deaths = malloc(data->philos_count * sizeof(pthread_mutex_t));
	data->meals = malloc(data->philos_count * sizeof(pthread_mutex_t));
	if (!data->forks || !data->deaths || !data->meals)
	{
		ft_free(data);
		return (ft_error(MALLOC_FAILED));
	}
	while (i < data->philos_count)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0 ||
			pthread_mutex_init(&(data->deaths[i]), NULL) != 0 ||
			pthread_mutex_init(&(data->meals[i]), NULL) != 0)
		{
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
		ft_error(MALLOC_FAILED);
	while (i < data->philos_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].fork_r = &(data->forks[i]);
		data->philos[i].fork_l = &(data->forks[(i + 1) % data->philos_count]);
		// assign death mutex
		// assign meal mutex
		data->philos[i].is_alive = 1; ///---> need it ?
		pthread_create(data->philos[i].thread, NULL, start_routine, data);
		i++;
	}
	return (0);
}
