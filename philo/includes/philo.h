/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:37:30 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/11 11:46:59 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_print.h"

/* --- libraries ------------------------------------------------------------ */
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/* --- structures ----------------------------------------------------------- */
typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_philo
{
	int			id;
	t_fork		fork_r;
	t_fork		fork_l;
	suseconds_t	last_meal;
	int			meals_eaten;
}				t_philo;

typedef struct s_data
{
	int		philos_count; // int
	int		time_to_die; // millisecond
	int		time_to_eat; // millisecond : 1 millisecond == 1000 microseconds
	int		time_to_sleep; // millisecond
	int		meals_to_eat; // int
	t_philo	*philos;
	t_fork	*forks;
}				t_data;

/* --- check & parsing ------------------------------------------------------ */
int		check_arg(char **argv, t_data *data);

/* --- data init & clear ---------------------------------------------------- */
int		init_forks(t_data *data);
int		init_philos(t_data *data);
int		destroy_forks(t_data *data);

/* --- utils ---------------------------------------------------------------- */
size_t	ft_strlen(char *str);

/* --- error handling  ------------------------------------------------------ */
int		ft_error(char *message);

#endif