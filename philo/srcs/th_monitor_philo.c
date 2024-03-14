/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:08:59 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/14 14:58:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->philo_state_mutex);
	if ((current_time() - philo->last_meal_time
			> philo->data->time_to_die && philo->state != EATING))
 	{
		pthread_mutex_lock(&philo->data->data_mutex);
		philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->data_mutex);
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_unlock(philo->philo_state_mutex);
		usleep(1000); ///// -----> Need to check
		print_state(philo, DIE);
 		return (0);
 	}
	pthread_mutex_unlock(philo->philo_state_mutex);
 	return (1);
}

int	update_state(t_philo *philo, int new_state)
{
	pthread_mutex_lock(philo->philo_state_mutex);
	philo->state = new_state;
	pthread_mutex_unlock(philo->philo_state_mutex);
	return (0);
}

int	check_state(t_philo *philo, int state)
{
	pthread_mutex_lock(philo->philo_state_mutex);
	if (philo->state == state)
	{
		pthread_mutex_unlock(philo->philo_state_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->philo_state_mutex);
	return (0);
}

int	finished_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	pthread_mutex_lock(philo->philo_state_mutex);
	if (philo->meals_count == philo->data->meals_to_eat)
	{
		philo->data->philos_count--;
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_unlock(philo->philo_state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_unlock(philo->philo_state_mutex);
	return (0);
}


