/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/14 14:54:16 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->fork_r);
	else
		pthread_mutex_lock(philo->fork_l);
	if (check_state(philo, DEAD) == 1 || is_end(philo->data))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->fork_r);
		else
			pthread_mutex_unlock(philo->fork_l);
		return (-1);
	}
	print_state(philo, TAKE_FORK);
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->fork_l);
	else
		pthread_mutex_lock(philo->fork_r);
	if (check_state(philo, DEAD) == 1 || is_end(philo->data))
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->fork_r);
		else
			pthread_mutex_unlock(philo->fork_l);
		return (-1);
	}
	print_state(philo, TAKE_FORK);
	return (0);
}

void	eat(t_philo *philo)
{
	update_state(philo, EATING);
	print_state(philo, EAT);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_lock(philo->philo_mutex); ///
	philo->last_meal_time = current_time();
	philo->end_of_life = philo->last_meal_time + philo->data->time_to_die;
	philo->meals_count++;
	pthread_mutex_unlock(philo->philo_mutex); ///
}

int	sleep_then_think(t_philo *philo)
{
	if (is_end(philo->data))
		return (1);
	update_state(philo, SLEEPING);
	print_state(philo, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	if (is_end(philo->data))
		return (1);
	update_state(philo, THINKING);
	print_state(philo, THINK);
	return (0);
}

void	print_state(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (ft_strcmp(message, DIE) == 0)
		printf(RED "%06ld %d %s" RESET, timestamp(philo->data), philo->id, message);
	else if (ft_strcmp(message, EAT) == 0)
		printf(GREEN "%06ld %d %s" RESET, timestamp(philo->data), philo->id, message);
	else
		printf("%06ld %d %s", timestamp(philo->data), philo->id, message);
	pthread_mutex_unlock(&philo->data->data_mutex);
}
