/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:48 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/11 13:38:46 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	// data->forks = malloc(data->philos_count * sizeof(t_fork));
	// if (!(data->forks))
	// 	ft_error(MALLOC_FAILED);
	while (i < data->philos_count)
	{
		pthread_mutex_init(&(data->forks[i]), NULL);
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
		// fork right
		if (i == 0)
			data->philos[i].fork_r = data->forks[data->philos_count - 1];
		else
			data->philos[i].fork_r = data->forks[i - 1];
		// fork left
		if (i == data->philos_count - 1)
			data->philos[i].fork_l = data->forks[0];
		else
			data->philos[i].fork_l = data->forks[i + 1];
		data->philos->last_meal_time = 0;
		data->philos->meals_eaten = 0;
		pthread_create(data->philos[i].thread, NULL, start_routine, data);
		i++;
	}
	return (0);
}
// free
