/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:42:49 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/15 10:26:00 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_routine(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = current_time();
	while (i < data->philos_count)
	{
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].end_of_life = data->philos[i].last_meal_time
			+ data->time_to_die; 
		if (pthread_create(&(data->philos[i].tid), NULL, routine,
				(void *)&data->philos[i]) != 0)
			return (handle_thread_error(data, i));
		i++;
	}
	if (pthread_create(&(data->tid), NULL, state_monitor, (void *)data) != 0)
		return (handle_thread_error(data, i));
	i = 0;
	while (i < data->philos_count)
	{
		pthread_join(data->philos[i].tid, NULL);
		i++;
	}
	pthread_join(data->tid, NULL);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->is_running)
	{
		while (!is_end(philo->data))
		{
			if (check_state(philo, DEAD) == 1 || is_end(philo->data))
				return (0);
			if (wait_forks(philo) == 0)
			{
				eat(philo);
				if (finished_meals(philo) == 1)
					return (0);
				if (sleep_then_think(philo) == 1)
					return (0);
			}
		}
	}
	return (0);
}

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
			if (!still_alive(&data->philos[i]))
			 	return (0);
			i++;
		}
		if (all_philos_finished(data) == 1)
			return (0);
		usleep(500); /*To avoid too frequent loop*/
	}
	return (0);
}
