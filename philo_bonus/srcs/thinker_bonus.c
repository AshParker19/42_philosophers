/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:13:46 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/11 01:48:21 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker_bonus.h"

int	main(int ac, char *av[])
{
	t_table	table;

	if (!parser(ac, av))
		return (PARSING_ERROR);
	if (!table_init(&table, ac, av, -1))
		return (INIT_ERROR);
	organize_table(&table);
}