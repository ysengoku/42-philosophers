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

static void	wait_forks(t_data *data, int i);
static void	eat(t_data *data, int i);
static void	sleep_then_think(t_data *data, int i);

void	*start_routine(void *arg)
{
	 (void)arg; //temporay setting
	 return (NULL); //temporay setting
}

void	routine(t_data *data, int i)
{
	data->philos[i].last_meal_time = get_current_time();
	while (data->philos[i].is_alive == 1)
	{
		// lock mutex death -----> will be unlock when die
		// lock mutex meal -----> will be unlock when he finished all meals
		wait_forks(data, i); // check time to die & unlock mutex death if die
		eat(data, i);
		sleep_then_think(data, i);	
	}
}

static void	wait_forks(t_data *data, int i)
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
	printf("%ld %d %s", get_current_time(), i + 1, TAKE_FORK);
	// check if time to die
	pthread_mutex_lock(fork2);
	printf("%ld %d %s", get_current_time(), i + 1, TAKE_FORK);
}

static void	eat(t_data *data, int i)
{
	printf("%ld %d %s", get_current_time(), i + 1, EAT);
	usleep(data->time_to_eat * 1000);
	data->philos[i].last_meal_time = get_current_time();
	data->philos[i].meals_eaten++;
	pthread_mutex_unlock(&(data->philos[i].fork_r));
	pthread_mutex_unlock(&(data->philos[i].fork_l));
}

static void	sleep_then_think(t_data *data, int i)
{	
	printf("%ld %d %s", get_current_time(), i + 1, SLEEP);
	usleep(data->time_to_sleep * 1000);
	printf("%ld %d %s", get_current_time(), i + 1, THINK);
}
