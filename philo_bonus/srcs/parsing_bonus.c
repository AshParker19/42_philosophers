/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 00:45:22 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/11 00:46:04 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_numeric(char *str)
{
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (0);
	if (!*str)
		return (0);
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	parser(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac > 6 || ac < 5 || ft_atoi(av[1]) == 0)
	{
		printf (RED"Wrong arguments!\n"RESET);
		return (0);
	}
	while (av[i])
	{
		if (ft_strlen(av[i]) > 10 || !ft_numeric(av[i]) || 
			ft_atoi(av[i]) > INT_MAX)
		{
			printf (RED"Wrong arguments!\n"RESET);
			return (0);
		}
		i++;
	}
	return (1);
}
