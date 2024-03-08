/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:37:30 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/08 11:16:07 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* --- libraries ------------------------------------------------------------ */
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/* --- colors --------------------------------------------------------------- */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

/* --- structures ----------------------------------------------------------- */
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
	int		philos_count; // int
	int		time_to_die; // millisecond
	int		time_to_eat; // millisecond = 1/1000 second
	int		time_to_sleep; // millisecond
	int		meals_to_eat; // int
	t_philo	*philos;
	t_fork	*forks;
}				t_data;

/* --- error messages ------------------------------------------------------- */
# define MALLOC_FAILED "Memory allocation failed."
# define INVALID_ARGC "Invalid number of arguments.\n\
Usage: ./philo (number_of_philosophers) (time_to_die) (time_to_eat) \
(time_to_sleep) (optional: number_of_times_each_philosopher_must_eat)"
# define TOOFEW_PHILO "There must be at least 1 philosopher."
# define NEGATIVE_NBR "Negative number is not accepted."
# define INVALID_NBR "Input is not valid number."

/* --- state messages ------------------------------------------------------- */
# define TAKE_FORK " has taken a fork\n"
# define EAT " is eating\n"
# define SLEEP " is sleeping\n"
# define THINK " is thinking\n"
# define DIE " died\n"

/* --- check & parsing ------------------------------------------------------ */
int		check_arg(char **argv, t_data *data);

/* --- utils ---------------------------------------------------------------- */
size_t	ft_strlen(char *str);

/* --- error handling  ------------------------------------------------------ */
int		ft_error(char *message);

#endif