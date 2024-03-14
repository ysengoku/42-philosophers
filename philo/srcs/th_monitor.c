/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:08:59 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/14 13:00:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*state_monitor(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philos_count)
		{
			if (!still_alive(&data->philos[i])) //reporting & philos' thread join befoer return here ?
			{
				// i = 0;
				// while (i < data->philos_count)
				// 	pthread_join(data->philos[i++].tid, NULL);
			 	return (0);
			}
			i++;
		}
		if (data->philos_count == 0) /* if everyone finished to eat all meals */
			return (0);
		usleep(100); /* To avoid too frequent loop */
	}
	return (0);
}

int	still_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	if ((current_time() - philo->last_meal_time
			> philo->data->time_to_die && philo->state != EATING))
 	{
		pthread_mutex_lock(&philo->data->main_state);
		philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->main_state);
		philo->state = DEAD;
		pthread_mutex_unlock(philo->state_mutex);
		print_state(philo, DIE);
 		return (0);
 	}
	pthread_mutex_unlock(philo->state_mutex);
 	return (1);
}

int	is_end(t_data *data)
{
	pthread_mutex_lock(&data->main_state);
	if (data->end)
	{
		pthread_mutex_unlock(&data->main_state);
		return (1);
	}
	pthread_mutex_unlock(&data->main_state);
	return (0);
}
