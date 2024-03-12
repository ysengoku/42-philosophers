/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/12 15:09:26 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_forks(t_data *data, int i, struct timeval *now);
static void	philo_eats(t_data *data, int i, struct timeval *now);
static void	philo_sleeps(t_data *data, int i, struct timeval *now);
static void	philo_thinks(int i, struct timeval *now);

void	*start_routine(void *arg)
{
	 (void)arg; //temporay setting
	 return (NULL); //temporay setting
}

void	routine(t_data *data, int i)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	data->philos[i].last_meal_time = ft_milliseconds(now);
	while (data->philos[i].is_alive == 1)
	{
		// lock mutex death -----> will be unlock when die
		// lock mutex meal -----> will be unlock when he finished all meals
		wait_forks(data, i, &now); // check time to die & unlock mutex death if die
		philo_eats(data, i, &now);
		philo_sleeps(data, i, &now);	
		philo_thinks(i, &now);
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
	printf("%ld %d %s", ft_milliseconds(*now), i + 1, TAKE_FORK);
	// check if time to die
	pthread_mutex_lock(fork2);
	gettimeofday(now, NULL);
	printf("%ld %d %s", ft_milliseconds(*now), i + 1, TAKE_FORK);
}

static void	philo_eats(t_data *data, int i, struct timeval *now)
{
		printf("%ld %d %s", ft_milliseconds(*now), i + 1, EAT);
		usleep(data->time_to_eat * 1000);
		gettimeofday(&now, NULL);
		data->philos[i].last_meal_time = ft_milliseconds(*now);
		data->philos[i].meals_eaten++;
		pthread_mutex_unlock(&(data->philos[i].fork_r));
		pthread_mutex_unlock(&(data->philos[i].fork_l));
}

static void	philo_sleeps(t_data *data, int i, struct timeval *now)
{	
	gettimeofday(&now, NULL);
	printf("%ld %d %s", ft_milliseconds(*now), i + 1, SLEEP);
	usleep(data->time_to_sleep * 1000);
}

static void	philo_thinks(int i, struct timeval *now)
{
	gettimeofday(&now, NULL);
	printf("%ld %d %s", ft_milliseconds(*now), i + 1, THINK);
}
