/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:37:30 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/29 09:50:22 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*----- includes -------------------------------------------------------------*/
# include "philo_print.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/*----- structures -----------------------------------------------------------*/
typedef struct s_data	t_data;

enum e_state
{
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	DEAD = 0
};

typedef struct s_fork
{
	pthread_mutex_t	fork_mutex;
	int				occupied;
}				t_fork;

typedef struct s_philo
{
	pthread_t		tid;
	int				is_running;
	t_data			*data;
	int				id;
	enum e_state	state;
	long			last_meal_time;
	long			end_of_life;
	int				meals_count;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	// t_fork			*fork_r;
	// t_fork			*fork_l;
	pthread_mutex_t	*philo_mutex;
}				t_philo;

typedef struct s_data
{
	pthread_t		tid;
	int				philos_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	long			start_time;
	int				finished_philos;
	int				end;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	// t_fork			*forks;
	pthread_mutex_t	*philo_mutex;
	pthread_mutex_t	data_mutex;
}				t_data;

/*----- data init & clear ----------------------------------------------------*/
int		check_arg(int argc, char **argv, t_data *data);
int		init_mutex(t_data *data);
int		init_philos(t_data *data);
void	clear_mutex(t_data *data);
void	ft_free(t_data *data);

/*----- routine & monitor ----------------------------------------------------*/
int		start_routine(t_data *data);
void	*routine(void *arg);
void	*state_monitor(void *arg);
int		wait_forks(t_philo *philo);
void	eat(t_philo *philo);
int		sleep_then_think(t_philo *philo);
int		still_alive(t_philo *philo);
int		is_end(t_data *data);
void	print_state(t_philo *philo, char *message);

/*----- utils ----------------------------------------------------------------*/
size_t	ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
long	current_time(void);
long	ft_timestamp(t_data *data);
void	ft_usleep(long time_in_ms);
int		update_state(t_philo *philo, enum e_state new_state);
int		check_state(t_philo *philo, enum e_state state);
int		all_philos_finished(t_data *data);
int		finished_all_meals(t_philo *philo);

/*----- error handling  ------------------------------------------------------*/
int		ft_error(char *message);
int		ft_error_free(char *message, t_data *data);
int		ft_error_clear_mutex(char *message, t_data *data);
int		handle_thread_error(t_data *data, int i);

#endif