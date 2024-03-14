/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:54:29 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/14 13:00:12 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int	update_state(t_philo *philo, int new_state)
{
	pthread_mutex_lock(philo->state_mutex);
	philo->state = new_state;
	pthread_mutex_unlock(philo->state_mutex);
	return (0);
}

int	check_state(t_philo *philo, int state)
{
	pthread_mutex_lock(philo->state_mutex);
	if (philo->state == state)
	{
		pthread_mutex_unlock(philo->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->state_mutex);
	return (0);
}

void	print_state(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->main_state);
	printf("%ld %d %s", current_time(), philo->id, message);
	pthread_mutex_unlock(&philo->data->main_state);
}
