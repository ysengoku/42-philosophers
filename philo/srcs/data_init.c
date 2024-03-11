/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:48 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/11 11:54:35 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->philos_count * sizeof(t_fork));
	if (!(data->forks))
		ft_error(MALLOC_FAILED);
	while (i++ < data->philos_count)
	{
		data->forks[i].id = i;
		pthread_mutex_init(&(data->forks[i].mutex), NULL);
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
	while (i++ < data->philos_count)
	{
		data->philos[i].id = i;
	// fork right
		if (data->philos->id == 1)
			data->philos->fork_r = data->forks[data->philos_count - 1];
		else
			data->philos->fork_r = data->forks[i - 2];
	// fork left
		if (data->philos->id == data->philos_count)
			data->philos->fork_l = data->forks[0];
		else
			data->philos->fork_l = data->forks[i];
		data->philos->last_meal = 0;
		data->philos->meals_eaten = 0;
	}
	return (0);
}
// free
