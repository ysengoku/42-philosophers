/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:30:20 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/14 08:35:41 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_PRINT_H
# define PHILO_PRINT_H

/*----- colors ---------------------------------------------------------------*/
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

/*----- state messages -------------------------------------------------------*/
# define TAKE_FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIE "died\n"

/*----- error messages -------------------------------------------------------*/
# define INVALID_ARGC "Invalid number of arguments.\n\
Usage: ./philo (number_of_philosophers) (time_to_die) (time_to_eat) \
(time_to_sleep) (optional: number_of_times_each_philosopher_must_eat)"
# define TOOFEW_PHILO "There must be at least 1 philosopher."
# define NEGATIVE_NBR "Negative number is not accepted."
# define INVALID_NBR "Input is not valid number."

# define MALLOC_FAILED "Memory allocation failed."
# define MUTEX_INIT_FAILED "Failed to initialize mutex."
# define THREAD_ERROR "A problem occurred with thread."

#endif