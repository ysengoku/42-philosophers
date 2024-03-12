/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:44:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/12 15:07:28 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->deaths)
		free(data->deaths);
	if (data->meals)
		free(data->meals);	
}

int	clear_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutexattr_destroy(&(data->deaths[i]));
		pthread_mutexattr_destroy(&(data->meals[i]));
		i++;
	}
	free(data->forks);
	free(data->deaths);
	free(data->meals);
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