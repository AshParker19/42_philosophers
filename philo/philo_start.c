/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/21 18:42:49 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int ac, char **av)
{
	table->ac = ac;
	table->av = av;
	table->thinker_counter = 1;
	table->first_thought = NULL;
	table->last_thought = NULL;
}

t_thinker *ft_add_back(t_table *table)
{
	t_thinker	*new_idea;
	
	new_idea = malloc(1 * sizeof(t_thinker));
	if (!new_idea)
		return (NULL);
	new_idea->lock_status = false;	
	if (!table->first_thought)
	{
		table->last_thought = new_idea;
		return (new_idea);
	}
	else
	{
		table->last_thought->next = new_idea;
		table->last_thought = new_idea;
		return (table->first_thought);
	}
}

void*	spawn_and_join(void *arg)
{
	arg = NULL;
	return (NULL);
}

void	place_thinker(t_table *table)
{
	static int	i;
	pthread_t	sage;

	while (i++ < ft_atoi(table->av[1]))
		table->first_thought = ft_add_back(table);
	pthread_create(&sage, NULL, spawn_and_join, (void *)table);
	pthread_join(sage, NULL);
}

int main(int ac, char *av[])
{
	t_table table;

	if ((ac > 6 || ac < 5) || parser(av))
	{
		printf ("Wrong arguments!\n");
		return (1);
	}
	table_init(&table, ac, av);
	place_thinker(&table);
}

