/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:08:59 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 11:29:01 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check all mutex death 
// check if everyone has finished to eat all meals

void	*monitor_status(void *arg)
{
	int		i;
	t_data	*data;
	
	data = (t_data*)arg;
	while (1)
	{
		i = 0;
		data->finished_philos = 0;
		while (i < data->philos_count)
		{
			pthread_mutex_lock(&(data->status_mutex[i]));
			if (data->philos[i].status == DEAD)
				return ;
			if (data->meals_to_eat > 0 && data->philos[i].status == FINISHED)
				data->finished_philos++;
			pthread_mutex_unlock(&(data->status_mutex[i]));
			i++;
		}
		if (data->finished_philos == data->philos_count)
			return ;
		usleep(5000); // To avoid too frequent loop
	}
}
