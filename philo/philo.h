/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:37:30 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/05 08:57:30 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ----- libraries ----- */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

/* ----- structures ----- */

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	state;
}				t_fork;

typedef struct s_philo
{
	int		id;
	t_fork	fork_r;
	t_fork	fork_l;
}				t_philo;

typedef struct s_data
{
	int		philos_count;
	long	time_to_eat;
	long	time_to_die;
	long	time_to_sleep;
	s_philo	*philos;
	s_fork	*forks;
}				t_data;

/* ----- error messages ----- */
# define INVALID_ARGC "Invalid number of arguments\nUsage: ./philo (number_of_philosophers) (time_to_die) (time_to_eat) (time_to_sleep) (optional: number_of_times_each_philosopher_must_eat)\n"

/* ----- utils ----- */
size_t	ft_strlen(char *str);
#endif