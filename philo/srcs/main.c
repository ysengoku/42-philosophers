/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:56:06 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/08 10:40:01 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
/*--- Check argc & argv ---*/
	if (check_arg(argc, argv) == 1)
		return (1);

/*--- Init data ---*/


/*--- Start therads ---*/


/*--- Clear & free ---*/
	
	return (0);
}


int	check_arg(int argc, char **argv)
{	
	int	i;
	int	j;

	i = 1;
	if (argc < 5 && argc > 6)
		return (ft_error(INVALID_ARGC));
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			while (argv[i][j] == ' ' || (argv[i][j] >= 9 && argv[i][j] >= 13))
				j++;
			if (argv[i][j] == '+')
				j++;
			if (argv[i][j] == '-')
				return (ft_error(NEGATIVE_NBR));
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (ft_error(INVALID_NBR));
		}
		if (ft_atoi_pos(argv[i++]) == -1)
			return (ft_error(INVALID_NBR));
	}
	return (0);
}
