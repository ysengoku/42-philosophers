/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:48 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/12 14:35:48 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->philos_count * sizeof(pthread_mutex_t));
	data->deaths = malloc(data->philos_count * sizeof(pthread_mutex_t));
	if (!data->forks == NULL)
		ft_error(MALLOC_FAILED);
	if (!data->deaths == NULL)
		ft_error(MALLOC_FAILED);
	while (i < data->philos_count)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
		pthread_mutex_init(&(data->deaths[i]), NULL);
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
		if (i == 0)
			data->philos[i].fork_r = &(data->forks[data->philos_count - 1]);
		else
			data->philos[i].fork_r = &(data->forks[i - 1]);
		if (i == data->philos_count - 1)
			data->philos[i].fork_l = &(data->forks[0]);
		else
			data->philos[i].fork_l = &(data->forks[i + 1]);
		data->philos[i].last_meal_time = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].is_alive = 1;
		pthread_create(data->philos[i].thread, NULL, start_routine, data);
		i++;
	}
	return (0);
}
