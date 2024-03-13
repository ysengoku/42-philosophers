/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 15:00:21 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_forks(t_philo *philo);
static void	eat(t_philo *philo);
static void	sleep_then_think(t_philo *philo);

int	start_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		if (pthread_create(&(data->philos[i].tid), NULL, routine,
				(void *)&data->philos[i] != 0))
			return (handle_thread_error(data, i));
		i++;
	}
	if (pthread_create(&(data->tid), NULL, monitor_status, (void *)&data) != 0)
		return (handle_thread_error(data, i));
	while (i < data->philos_count)
	{
		pthread_join(data->philos[i].tid, NULL);
		i++;
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	philo = (t_philo *)arg;
	data = &(philo->data);
	i = philo->id - 1;
	philo->last_meal_time = current_time();
	if (philo->is_running)
	{
		while (1)
		{
			wait_forks(philo);
			eat(philo);
			if (philo->meals_count == data->meals_to_eat)
			{
				philo->data->philos_count--;
				return ;
			}
			sleep_then_think(philo);
		}
	}
}

static void	wait_forks(t_philo *philo)
{
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;

	if (philo->id != philo->data->philos_count)
	{
		fork1 = philo->fork_r;
		fork2 = philo->fork_l;
	}
	else
	{
		fork1 = philo->fork_l;
		fork2 = philo->fork_r;
	}
	pthread_mutex_lock(fork1);
	printf("%ld %d %s", current_time(), philo->id, TAKE_FORK);
	pthread_mutex_lock(fork2);
	printf("%ld %d %s", current_time(), philo->id, TAKE_FORK);
	return (0);
}

static void	eat(t_philo *philo)
{
	update_status(philo, EATING);
	printf("%ld %d %s", current_time(), philo->id, EAT);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&(philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	philo->last_meal_time = current_time();
	philo->meals_count++;
}

static void	sleep_then_think(t_philo *philo)
{
	update_status(philo, SLEEP);
	printf("%ld %d %s", current_time(), philo->id, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	update_status(philo, THINKING);
	printf("%ld %d %s", current_time(), philo->id, THINK);
}
