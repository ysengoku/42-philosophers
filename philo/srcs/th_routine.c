/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/30 10:03:20 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_forks(t_philo *philo)
{
	take_first_fork(philo);
	// usleep(100);
	if (check_state(philo, DEAD) == 1 || is_end(philo->data))
		return (release_forks(philo, 1));
	print_state(philo, TAKE_FORK);
	if (take_second_fork(philo) == 1)
		return (release_forks(philo, 1));
	// usleep(100);
	if (check_state(philo, DEAD) == 1 || is_end(philo->data))
		return (release_forks(philo, 2));
	print_state(philo, TAKE_FORK);
	return (0);
}

void	eat(t_philo *philo)
{
	if (check_state(philo, DEAD) == 1 || is_end(philo->data))
	{
		release_forks(philo, 2);
		return ;
	}
	update_state(philo, EATING);
	print_state(philo, EAT);
	philo->last_meal_time = current_time();
	philo->end_of_life = philo->last_meal_time + philo->data->time_to_die;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->p_mutex);
	philo->meals_count++;
	pthread_mutex_unlock(&philo->p_mutex);
	release_forks(philo, 2);
}

int	sleep_then_think(t_philo *philo)
{
	if (is_end(philo->data))
		return (1);
	update_state(philo, SLEEPING);
	print_state(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
	if (is_end(philo->data))
		return (1);
	update_state(philo, THINKING);
	print_state(philo, THINK);
	return (0);
}

void	print_state(t_philo *philo, char *message)
{
	if (ft_strcmp(message, DIE) == 0)
	{
		printf("%06ld %d %s", ft_timestamp(philo->data),
			philo->id, message);
	}
	else
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		printf("%06ld %d %s", ft_timestamp(philo->data), philo->id, message);
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
}
