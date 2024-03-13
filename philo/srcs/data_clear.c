/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:44:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 15:05:05 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data)
{
	if (data->forks)
		free(data->forks);
	if (data->status_mutex)
		free(data->status_mutex);
	if (data->philos)
		free(data->philos);
}

void	clear_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(data->status_mutex[i]));
		i++;
	}
	if (data->forks)
		free(data->forks);
	if (data->status_mutex)
		free(data->status_mutex);
	if (data->philos)
		free(data->philos);
	return (0);
}

// int	clear_thread(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->philos_count)
// 	{
// 		pthread_join(data->philos[i].tid, NULL);
// 		i++;
// 	}
// 	free(data->philos);
// }
