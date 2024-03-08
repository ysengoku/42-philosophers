/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 08:54:29 by yusengok          #+#    #+#             */
/*   Updated: 2024/03/08 10:21:22 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi_pos(char *arg)
{
	int		i;
	long	nbr;

	i = 0;
	nbr = 0;
	while ((arg[i] >= 9 && arg[i] <= 13) || arg[i] == ' ')
		i++;
	if (arg[i] == '+')
		i++;
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		nbr += (arg[i] - '0');
		if (arg[i + 1] >= '0' && arg[i + 1] <= '9')
			nbr *= 10;
		else if (nbr > LONG_MAX / 10 || (nbr == LONG_MAX / 10 && arg[i] - '0' > 7))
			return (-1);
		i++;
	}
	return ((int)nbr);
}
