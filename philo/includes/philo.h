/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:37:30 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 15:05:14 by yusengok         ###   ########.fr       */
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
typedef struct s_data	t_data;

# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define DEAD 0

typedef struct s_philo
{
	pthread_t		tid;
	int				is_running;
	t_data			*data;
	int				id;
	int				state;
	long			last_meal_time;
	int				meals_count;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*state_mutex;
}				t_philo;

typedef struct s_data
{
	int				philos_count;
	int				time_to_die; // millisecond
	int				time_to_eat; // millisecond : 1 millisecond == 1000 microseconds
	int				time_to_sleep; // millisecond
	int				meals_to_eat; // -1 if it's not given in arguments
	int				end;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*state_mutex;
	pthread_t		tid;
}				t_data;

/*----- data init & clear ----------------------------------------------------*/
int		check_arg(int argc, char **argv, t_data *data);
int		init_mutex(t_data *data);
int		init_philos(t_data *data);
void	clear_mutex(t_data *data);
// int		clear_thread(t_data *data);
void	ft_free(t_data *data);

/*----- routine --------------------------------------------------------------*/
int		start_routine(t_data *data);
void	*routine(void *arg);
void	*monitor_status(void *arg);
int		still_alive(t_philo *philo);

/*----- utils ----------------------------------------------------------------*/
size_t	ft_strlen(char *str);
long	current_time(void);
void	update_state(t_philo *philo, int new_state);

/*----- error handling  ------------------------------------------------------*/
int		ft_error(char *message);
int		ft_error_free(char *message, t_data *data);
int		ft_error_clear_mutex(char *message, t_data *data);
int		handle_thread_error(t_data *data, int i);

#endif