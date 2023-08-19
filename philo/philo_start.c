/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/19 18:00:58 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int ac, char **av)
{
	table->ac = ac;
	table->av = av;
	table->thinker_counter = 1;
	table->thinker = NULL;
	table->last_thought = NULL;
}


t_thinker *ft_add_back(t_table *table)
{
	t_thinker	*new_idea;
	
	new_idea = malloc(1 * sizeof(t_thinker));
	if (!new_idea)
		return (NULL);
	pthread_create(&new_idea->thought, NULL, take_a_fork, (void *) table);
	if (!table->thinker)
	{
		table->last_thought = new_idea;
		return (new_idea);
	}
	else
	{
		table->last_thought->next = new_idea;
		new_idea->prev = table->last_thought;
		table->last_thought = new_idea;
		return (table->thinker);
	}
}


void	spawn_and_join_thinker(t_table *table)
{
	int			i;
	t_thinker	*current;

	i = -1;
	while (++i < ft_atoi(table->av[1]))
		table->thinker = ft_add_back(table);
	current = table->thinker;
	while (current)
	{
		pthread_join(current->thought, NULL);
		current = current->next;
	}
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
	pthread_mutex_init(&table.lock, NULL);
	spawn_and_join_thinker(&table);
	pthread_mutex_destroy(&table.lock);
}

// circular linked list. the pointers to prev and next are forks, check if mutex is not
// locked in the next one