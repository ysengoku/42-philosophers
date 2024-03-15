/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:56:06 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/15 10:42:58 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(INVALID_ARGC));
	if (check_arg(argc, argv, &data) == 1)
		return (1);
	if (data.philos_count == 1)
	{
		usleep(data.time_to_die * 1000);
		printf(RED "%ld %d %s" RESET, current_time(), 1, DIE);
		return (0);
	}
	if (init_mutex(&data) == 1)
		return (1);
	if (init_philos(&data) == 1)
		return (1);
	if (start_routine(&data) == 1)
		return (1);
	clear_mutex(&data);
	return (0);
}
