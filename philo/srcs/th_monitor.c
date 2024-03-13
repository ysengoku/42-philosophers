/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:08:59 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 15:06:53 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//static int	is_alive(t_philo *philo);

void	*monitor_status(void *arg)
{
	int		i;
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->philos_count)
		{
			// if (!is_alive(&data->philos[i]))
			// 	return ;
			pthread_mutex_lock(&(data->status_mutex[i]));
			if (current_time() - data->philos[i].last_meal_time
				> data->time_to_die && data->philos[i].status != EATING)
				return (printf("%ld %d %s", current_time(), i + 1, DIE));
			pthread_mutex_unlock(&(data->status_mutex[i]));
			i++;
		}
		if (data->philos_count == 0)
			return ;
		usleep(5000); // To avoid too frequent loop
	}
}

// static int	is_alive(t_philo *philo)
// {
// 	if (current_time() - philo->last_meal_time > philo->data->time_to_die)
// 	{
// 		pthread_mutex_lock(&(philo->status_mutex));
// 		if (philo->status != EATING)
// 		{
// 			printf("%ld %d %s", current_time(), philo->id, DIE);
// 			return (0);
// 		}
// 		pthread_mutex_unlock(&(philo->status_mutex));
// 	}
// 	return (1);
// }
