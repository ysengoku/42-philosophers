/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:18:48 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/29 11:12:00 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_data *data);
static int	init_philos(t_data *data);
static void	init_philo_content(t_data *data, int i);

int	init_data(t_data *data)
{
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (ft_error_free(MUTEX_INIT_FAILED, data));
	if (init_forks(data) == 1)
		return (1);
	if (init_philos(data) == 1)
		return (1);
	return (0);
}

static int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(data->philos_count * sizeof(t_fork));
	if (data->forks == NULL)
	{
		pthread_mutex_destroy(&data->data_mutex);
		return (ft_error_free(MALLOC_FAILED, data));
	}
	while (i < data->philos_count)
	{
		
		if (pthread_mutex_init(&data->forks[i].f_mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&data->forks[i--].f_mutex);
			pthread_mutex_destroy(&data->data_mutex);
			return (ft_error_free(MUTEX_INIT_FAILED, data));
		}
		data->forks[i].occupied = 0;
		i++;
	}
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(data->philos_count * sizeof(t_philo));
	if (!(data->philos))
	{
		while (i < data->philos_count)
			pthread_mutex_destroy(&data->forks[i++].f_mutex);
		return (ft_error_clear_mutex(MALLOC_FAILED, data));
	}
	while (i < data->philos_count)
	{
		if (pthread_mutex_init(&data->philos[i].p_mutex, NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&data->philos[i--].p_mutex);
			while (i < data->philos_count)
				pthread_mutex_destroy(&data->forks[i++].f_mutex);
			pthread_mutex_destroy(&data->data_mutex);
			return (ft_error_free(MUTEX_INIT_FAILED, data));
		}
		init_philo_content(data, i);
		i++;
	}
	return (0);
}

static void	init_philo_content(t_data *data, int i)
{
	data->philos[i].data = data;
	data->philos[i].id = i + 1;
	data->philos[i].state = THINKING;
	data->philos[i].last_meal_time = 0;
	data->philos[i].end_of_life = 0;
	data->philos[i].meals_count = 0;
	data->philos[i].fork_r = &(data->forks[i]);
	data->philos[i].fork_l = &(data->forks[(i + 1) % data->philos_count]);
	data->philos[i].is_running = 1;
}
