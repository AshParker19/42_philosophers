/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/18 21:29:45 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int ac, char **av)
{
	table->ac = ac;
	table->av = av;
	table->thinker = NULL;
	table->last_thought = NULL;
}

void	*take_a_fork(void *thinker)
{
	int	*num;

	num = (int*)thinker;
	printf ("%d has taken a fork\n", *num);
	return (NULL);
}

t_thinker *ft_listadd_back(t_table *table, int i)
{
	t_thinker	*new_idea;
	
	new_idea = malloc(1 * sizeof(t_thinker));
	if (!new_idea)
		return (NULL);
	pthread_create(&new_idea->thought, NULL, take_a_fork, (void *) &i);
	if (!table->thinker)
	{
		table->last_thought = new_idea;
		return (new_idea);
	}
	else
	{
		table->thinker->next = new_idea;
		new_idea->prev = table->thinker;
		table->thinker = new_idea;
		return (table->thinker);
	}
}


void	spawn_thinker(t_table *table)
{
	int	i;
	int	thinker_num;

	i = 1;
	thinker_num = ft_atoi(table->av[1]);
	while (i <= thinker_num)
		ft_listadd_back(table, i++);
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
	spawn_thinker(&table);
	if (table.thinker)
		printf ("The smart cunts are here\n");
}

// circular linked list. the pointers to prev and next are forks, check if mutex is not
// locked in the next one