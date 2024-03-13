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
				(void *)&data->philos[i]) != 0)
			return (handle_thread_error(data, i));
		i++;
	}
	if (pthread_create(&(data->tid), NULL, monitor_status, (void *)data) != 0)
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
	philo->last_meal_time = current_time();
	if (philo->is_running)
	{
		while (!philo->data->end)
		{
			wait_forks(philo);
			if (!still_alive(philo))
			{
				update_state(philo, DEAD);
				return (0);
			}
			eat(philo);
			if (philo->meals_count == philo->data->meals_to_eat)
			{
				philo->data->philos_count--;
				return (0);
			}
			sleep_then_think(philo);
		}
	}
	return (0);
}

static void	wait_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->fork_r);
	else
		pthread_mutex_lock(philo->fork_l);
	printf("%ld %d %s", current_time(), philo->id, TAKE_FORK);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->fork_l);
	else
		pthread_mutex_lock(philo->fork_r);
	printf("%ld %d %s", current_time(), philo->id, TAKE_FORK);
}

static void	eat(t_philo *philo)
{
	update_state(philo, EATING);
	printf("%ld %d %s", current_time(), philo->id, EAT);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	philo->last_meal_time = current_time();
//	if (philo->data->meals_to_eat > 0)
	philo->meals_count++;
}

static void	sleep_then_think(t_philo *philo)
{
	update_state(philo, SLEEPING);
	printf("%ld %d %s", current_time(), philo->id, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	update_state(philo, THINKING);
	printf("%ld %d %s", current_time(), philo->id, THINK);
}
