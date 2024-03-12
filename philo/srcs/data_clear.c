/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:44:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/12 14:35:03 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clear_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutexattr_destroy(&(data->deaths[i]));
		i++;
	}
	free(data->forks);
	free(data->deaths);
	return (0);
}

int	clear_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		// thread
	}
	free(data->philos);
}