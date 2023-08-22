/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:08:18 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/18 14:45:12 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_atoi(const char *nptr)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res *= 10;
		res += nptr[i] - 48;
		i++;
	}
	return (res * sign);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
	{
		write (1, "gettimeofday() error\n", 22);
		return (1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(useconds_t ms)
{
	u_int64_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < ms)
		usleep(ms / 10);
	return (0);	
}