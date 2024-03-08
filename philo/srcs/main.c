/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:56:06 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/08 10:59:51 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error(MALLOC_FAILED);
/*--- Check argc & argv ---*/
	if (check_arg(argc, argv, data) == 1)
		return (1);

/*--- Init data ---*/


/*--- Start therads ---*/


/*--- Clear & free ---*/
	
	// free(data);
	return (0);
}
