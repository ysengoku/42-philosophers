/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_monitor_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:08:59 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/29 11:02:18 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->p_mutex);
	if ((current_time() > philo->end_of_life && philo->state != EATING))
	{
		philo->state = DEAD;
		pthread_mutex_unlock(&philo->p_mutex);
		pthread_mutex_lock(&philo->data->data_mutex);
		print_state(philo, DIE);
		philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->p_mutex);
	return (1);
}

int	update_state(t_philo *philo, enum e_state new_state)
{
	pthread_mutex_lock(&philo->p_mutex);
	philo->state = new_state;
	pthread_mutex_unlock(&philo->p_mutex);
	return (0);
}

int	check_state(t_philo *philo, enum e_state state)
{
	pthread_mutex_lock(&philo->p_mutex);
	if (philo->state == state)
	{
		pthread_mutex_unlock(&philo->p_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->p_mutex);
	return (0);
}

int	finished_all_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	pthread_mutex_lock(&philo->p_mutex);
	if (philo->meals_count == philo->data->meals_to_eat)
	{
		pthread_mutex_unlock(&philo->p_mutex);
		philo->data->finished_philos++;
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_unlock(&philo->p_mutex);
	return (0);
}
