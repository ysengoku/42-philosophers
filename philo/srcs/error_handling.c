/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:32:11 by yusengok          #+#    #+#             */
/*   Updated: 2024/04/29 11:11:08 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *message)
{
	write(2, "[Error] ", 9);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (1);
}

int	ft_error_free(char *message, t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	write(2, "[Error] ", 10);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (1);
}

int	ft_error_clear_mutex(char *message, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&(data->forks[i].f_mutex));
		pthread_mutex_destroy(&(data->philos[i].p_mutex));
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
	printf(RED "[Error] " RESET);
	printf("%s\n", message);
	return (1);
}

int	handle_thread_error(t_data *data, int i)
{
	while (i > 0)
	{
		data->philos[i].is_running = 0;
		pthread_join(data->philos[i].tid, NULL);
		i--;
	}
	return (ft_error_clear_mutex(THREAD_ERROR, data));
}
