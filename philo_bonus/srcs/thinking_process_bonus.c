/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking_process_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 01:50:04 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/12 14:41:44 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker_bonus.h"

void	thinking_process(t_thinker *thinker)
{
	if (thinker->id % 2)
		ft_usleep(10);
	existence(thinker);		
}

void	organize_table(t_table *table)
{
	uint64_t		i;
	t_thinker		*current;

	i = 1;
	while (i <= table->thinker_num)
		table->first_thought = ft_add_back(table, i++);
	current = table->first_thought;
	while (current)
	{
		current->pid = fork();
		if (current->pid == 0)
			thinking_process(current);
		current = current->next;	
	}
	wait_thinkers(table);
}

void	existence(t_thinker *thinker)
{
	int i = 10;
	while (--i)
	{
		if (thinker->table->dead)
			break ;
		sem_wait(thinker->table->key);	
		pick_up_forks(thinker);
		eat(thinker);
		put_down_forks(thinker);
		ft_usleep(thinker->table->time_to_sleep);
		log_action(thinker, THINK);
	}
	exit(1);
}
