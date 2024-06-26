/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitoir_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:47:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/30 12:09:00 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_end(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	if (data->end)
	{
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

int	all_philos_finished(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	if (data->finished_philos == data->philos_count && data->meals_to_eat != -1)
	{
		data->end = 1;
		// printf("%06ld ", ft_timestamp(data));
		// printf(GREEN "Everyone has finished to eat\n" RESET);
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}
