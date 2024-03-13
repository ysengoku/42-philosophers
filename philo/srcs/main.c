/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:56:06 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/13 15:05:28 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (ft_error(INVALID_ARGC));
/*--- Check argc & argv ---*/
	if (check_arg(argv, &data) == 1)
		return (1);
	if (data.philos_count == 1) // He can never eat
	{
		usleep(data.time_to_die * 1000);
		printf("%ld %d %s", current_time(), data.philos[0].id, DIE);
		return (0);
	}
/*--- Init data ---*/
	if (init_mutex(&data) == 1)
		return (1);
/*--- Start therads ---*/
	if (start_routine(&data) == 1)
		return (1);
/*--- Clear & free ---*/
	clear_mutex(&data);
	return (0);
}
