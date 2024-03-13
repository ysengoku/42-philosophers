/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:30:46 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 11:25:52 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_forks(t_philo *philo);
static void	eat(t_philo *philo);
static void	sleep_then_think(t_philo *philo);

void	start_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_create(&(data->philos[i].tid), NULL, routine,
			(void *)&data->philos[i]);
		i++;
	}
	pthread_create(&(data->tid), NULL, monitor_status, (void *)&data);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int	i;

	philo = (t_philo *)arg;
	data = &(philo->data);
	i = philo->id - 1;
	philo->last_meal_time = get_current_time();
	while (philo->status != DEAD || philo->status != FINISHED)
	{
		wait_forks(philo); // check time to die & change status if die
		eat(philo);
		// check if he ate all meals. If yes, change status and finish rootine (break ;)
		sleep_then_think(philo);	
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
	// check if time to die
	pthread_mutex_lock(fork1);
	printf("%ld %d %s", get_current_time(), philo->id, TAKE_FORK);
	// check if time to die
	pthread_mutex_lock(fork2);
	printf("%ld %d %s", get_current_time(), philo->id, TAKE_FORK);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->status_mutex));
	philo->status = EATING;
	pthread_mutex_unlock(&(philo->status_mutex));
	printf("%ld %d %s", get_current_time(), philo->id, EAT);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&(philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	philo->last_meal_time = get_current_time();
	philo->meals_count++;
}

static void	sleep_then_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->status_mutex));
	philo->status = SLEEPING;
	pthread_mutex_unlock(&(philo->status_mutex));
	printf("%ld %d %s", get_current_time(), philo->id, SLEEP);
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_lock(&(philo->status_mutex));
	philo->status = THINKING;
	pthread_mutex_unlock(&(philo->status_mutex));
	printf("%ld %d %s", get_current_time(), philo->id, THINK);
}
