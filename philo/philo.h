/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 08:37:30 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/08 10:34:32 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ----- libraries ----- */
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

/* ----- colors ----- */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

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
	t_philo	*philos;
	t_fork	*forks;
}				t_data;

/* ----- error messages ----- */
# define INVALID_ARGC "Invalid number of arguments.\n"
# define NEGATIVE_NBR "Negative number is not accepted.\n"
# define INVALID_NBR "Input is not valid number.\n"

/* ----- utils ----- */
size_t	ft_strlen(char *str);
int		ft_atoi_pos(char *arg);

/* ----- error handling  ----- */
int	ft_error(char *message);

#endif