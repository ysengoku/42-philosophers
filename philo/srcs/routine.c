/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/11 15:09:14 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine(t_data *data, int i);
static void	wait_forks(t_data *data, int i, struct timeval *now);

void	*start_routine(t_data *data)
{

}

static void	routine(t_data *data, int i)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	data->philos->last_meal_time = milliseconds(now);
	while (1)
	{
		wait_forks(data, i, &now);
	/*--- eat ---*/
		printf("%ld %d %s", milliseconds(now), i + 1, EAT);
		usleep(data->time_to_eat * 1000);
		gettimeofday(&now, NULL);
		data->philos[i].last_meal_time = milliseconds(now);
		data->philos[i].meals_eaten++;
		pthread_mutex_unlock(&(data->philos[i].fork_r));
		pthread_mutex_unlock(&(data->philos[i].fork_l));
	/*--- sleep ---*/
		gettimeofday(&now, NULL);
		printf("%ld %d %s", milliseconds(now), i + 1, SLEEP);
		usleep(data->time_to_sleep * 1000);
	/*--- think ---*/
		gettimeofday(&now, NULL);
		printf("%ld %d %s", milliseconds(now), i + 1, THINK);
	}
}

static void	wait_forks(t_data *data, int i, struct timeval *now)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	if (i != data->philos_count -1)
	{
		fork1 = &(data->philos[i].fork_r);
		fork2 = &(data->philos[i].fork_l);
	}
	else
	{
		fork1 = &(data->philos[i].fork_l);
		fork2 = &(data->philos[i].fork_r);
	}
	// check if time to die
	pthread_mutex_lock(fork1);
	gettimeofday(now, NULL);
	printf("%ld %d %s", milliseconds(*now), i + 1, TAKE_FORK);
	// check if time to die
	pthread_mutex_lock(fork2);
	gettimeofday(now, NULL);
	printf("%ld %d %s", milliseconds(*now), i + 1, TAKE_FORK);
}
