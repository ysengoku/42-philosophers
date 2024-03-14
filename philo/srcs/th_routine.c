/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/14 13:00:26 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	wait_forks(t_philo *philo);
static void	eat(t_philo *philo);
static int	sleep_then_think(t_philo *philo);

int	start_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		data->philos[i].last_meal_time = current_time();
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
		while (!is_end(philo->data)) // --> need to check if this condition works
		{
			if (check_state(philo, DEAD) == 1)
			// if (philo->state == DEAD)
				return (0);
			if (wait_forks(philo) == 0)
			{
				eat(philo);
				if (philo->meals_count == philo->data->meals_to_eat)
				{
					philo->data->philos_count--;
					return (0);
				}
				if (sleep_then_think(philo) == 1)
					return (0);
			}
		}
	}
	return (0);
}

static int	wait_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->fork_r);
	else
		pthread_mutex_lock(philo->fork_l);
	print_state(philo, TAKE_FORK);
	//printf("%ld %d %s", current_time(), philo->id, TAKE_FORK);
	if (check_state(philo, DEAD) == 1)
	// if (philo->state == DEAD)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->fork_r);
		else
			pthread_mutex_unlock(philo->fork_l);
		return (-1);
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->fork_l);
	else
		pthread_mutex_lock(philo->fork_r);
		
	// if (philo->id % 2 == 0)
	// {
	// 	if (pthread_mutex_lock(philo->fork_l) != 0)
	// 	{
	// 		pthread_mutex_unlock(philo->fork_r);
	// 		return (1);
	// 	}
	// }
	// else
	// {
	// 	if (pthread_mutex_lock(philo->fork_r) != 0)
	// 	{
	// 		pthread_mutex_unlock(philo->fork_l);
	// 		return (1);
	// 	}
	// }
	print_state(philo, TAKE_FORK);
	// printf("%ld %d %s", current_time(), philo->id, TAKE_FORK);
	return (0);
}

static void	eat(t_philo *philo)
{
	update_state(philo, EATING);
	// printf(GREEN "%ld " RESET, current_time());
	// printf("%d %s", philo->id, EAT);
	// printf("%ld %d %s", current_time(), philo->id, EAT);
	print_state(philo, EAT);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	philo->last_meal_time = current_time();
//	if (philo->data->meals_to_eat > 0)
	philo->meals_count++;
}

static int	sleep_then_think(t_philo *philo)
{
	if (is_end(philo->data))
		return (1);
	update_state(philo, SLEEPING);
	// printf("%ld %d %s", current_time(), philo->id, SLEEP);
	print_state(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	if (is_end(philo->data))
		return (1);
	update_state(philo, THINKING);
	print_state(philo, THINK);
	return (0);
}
