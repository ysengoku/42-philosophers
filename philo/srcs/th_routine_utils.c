/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_routine_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 11:43:35 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/30 09:53:01 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_first_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork_r->f_mutex);
		philo->fork_r->occupied = 1;
	}
	else
	{
		pthread_mutex_lock(&philo->fork_l->f_mutex);
		philo->fork_l->occupied = 1;
	}
}

int	take_second_fork(t_philo *philo)
{
	if (philo->id % 2 == 0 && philo->fork_l != NULL)
	{
		pthread_mutex_lock(&philo->fork_l->f_mutex);
		philo->fork_l->occupied = 1;
	}
	else if (philo->id % 2 != 0 && philo->fork_r != NULL)
	{
		pthread_mutex_lock(&philo->fork_r->f_mutex);
		philo->fork_r->occupied = 1;
	}
	else
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_lock(&philo->p_mutex);
		philo->state = DEAD;
		pthread_mutex_lock(&philo->data->data_mutex);
		philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->data_mutex);
		pthread_mutex_unlock(&philo->p_mutex);
		return (1);
	}
	return (0);
}

int	release_forks(t_philo *philo, int fork_count)
{
	if (philo->id % 2 == 0)
	{
		philo->fork_r->occupied = 0;
		pthread_mutex_unlock(&philo->fork_r->f_mutex);
	}
	else
	{
		philo->fork_l->occupied = 0;
		pthread_mutex_unlock(&philo->fork_l->f_mutex);
	}
	if (fork_count == 2)
	{
		if (philo->id % 2 == 0)
		{
			philo->fork_l->occupied = 0;
			pthread_mutex_unlock(&philo->fork_l->f_mutex);
		}
		else
		{
			philo->fork_r->occupied = 0;
			pthread_mutex_unlock(&philo->fork_r->f_mutex);
		}
	}
	return (1);
}
