/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 01:50:04 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/11 02:24:19 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker_bonus.h"

void	organize_table(t_table *table)
{
	uint64_t		i;
	t_thinker		*current;

	i = 1;
	while (i <= table->thinker_num)
		table->first_thought = ft_add_back(table, i++);
	current = table->first_thought;
	// while (current)
	// {
		
	// }
}