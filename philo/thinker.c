/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 02:06:14 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/09 21:21:27 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker.h"

int	main(int ac, char *av[])
{
	t_table	table;

	if (!parser(ac, av))
		return (PARSING_ERROR);
	if (!table_init(&table, ac, av, -1))
		return (INIT_ERROR);
	organize_table(&table);
}
