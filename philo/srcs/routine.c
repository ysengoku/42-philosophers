/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/11 14:45:43 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	routine(t_data *data, int i);
static void	wait_fork(t_data *data, int i, struct timeval tv);

void	*start_routine(t_data *data)
{

}

static void	routine(t_data *data, int i)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	data->philos->last_meal_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (1)
	{
		wait_forks(data, i, &tv);
	/*--- eat ---*/
		printf("%ld %d %s", tv.tv_sec * 1000 + tv.tv_usec / 1000, i + 1, EAT);
		usleep(data->time_to_eat * 1000);
		gettimeofday(&tv, NULL);
		data->philos[i].last_meal_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		data->philos[i].meals_eaten++;
		pthread_mutex_unlock(&(data->philos[i].fork_r));
		pthread_mutex_unlock(&(data->philos[i].fork_l));
	/*--- sleep ---*/
		gettimeofday(&tv, NULL);
		printf("%ld %d %s", tv.tv_sec * 1000 + tv.tv_usec / 1000,
			i + 1, SLEEP);
		usleep(data->time_to_sleep * 1000);
	/*--- think ---*/
		gettimeofday(&tv, NULL);
		printf("%ld %d %s", tv.tv_sec * 1000 + tv.tv_usec / 1000,
			i + 1, THINK);
	}
}

static void	wait_forks(t_data *data, int i, struct timeval *tv)
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
	gettimeofday(tv, NULL);
	printf("%ld %d %s", tv->tv_sec * 1000 + tv->tv_usec / 1000,
		i + 1, TAKE_FORK);
	// check if time to die
	pthread_mutex_lock(fork2);
	gettimeofday(tv, NULL);
	printf("%ld %d %s", tv->tv_sec * 1000 + tv->tv_usec / 1000,
		i + 1, TAKE_FORK);
}
