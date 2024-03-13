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
			if (!still_alive(&data->philos[i])) //--> death state check? reporting & philos' thread join befoer return here ?
			 	return (0);
			i++;
		}
		if (data->philos_count == 0) // if everyone finished to eat all meals
			return (0);
		usleep(100); // To avoid too frequentloop
	}
	return (0);
}

int	still_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->state_mutex);
	if ((current_time() - philo->last_meal_time > philo->data->time_to_die
			&& philo->state != EATING) || philo->state == DEAD)
 	{
 		printf("%ld %d %s", current_time(), philo->id, DIE);
		philo->data->end = 1;
 		return (0);
 	}
	pthread_mutex_unlock(philo->state_mutex);
 	return (1);
}
