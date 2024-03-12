/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:37:30 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/12 15:06:15 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_print.h"

/*----- libraries ------------------------------------------------------------*/
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/*----- structures -----------------------------------------------------------*/
typedef struct s_philo
{
	pthread_t		thread;
	t_data			*data;
	int				id;
	long			last_meal_time;
	int				meals_eaten;
	int				is_alive;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*death;
}				t_philo;

typedef struct s_data
{
	int				philos_count; // int
	int				time_to_die; // millisecond
	int				time_to_eat; // millisecond : 1 millisecond == 1000 microseconds
	int				time_to_sleep; // millisecond
	int				meals_to_eat; // int
	t_philo			*philos;
	// t_fork	*forks;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*deaths;
	pthread_mutex_t	*meals;
}				t_data;

/*----- check & parsing ------------------------------------------------------*/
int		check_arg(char **argv, t_data *data);

/*----- data init & clear ----------------------------------------------------*/
int		init_mutex(t_data *data);
int		init_philos(t_data *data);
int		clear_mutex(t_data *data);
int		clear_philos(t_data *data);
void	ft_free(t_data *data);

/*----- routine --------------------------------------------------------------*/
void	*start_routine(void *arg);

/*----- utils ----------------------------------------------------------------*/
size_t	ft_strlen(char *str);
long	get_current_time(void);
//long	ft_milliseconds(struct timeval time);

/*----- error handling  ------------------------------------------------------*/
int		ft_error(char *message);

#endif