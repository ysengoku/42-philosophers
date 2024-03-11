/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:44:38 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/11 11:48:38 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	clear_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&(data->forks[i].mutex));
		i++;
	}
	free(data->forks);
	return (0);
}
