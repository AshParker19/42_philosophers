/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 17:14:39 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/02 16:18:35 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int ac, char **av, int i)
{
	table->ac = ac;
	table->dead = false;
	table->start_time = get_current_time();
	table->thinker_num = ft_atoi(av[1]);
	table->forks = ft_calloc(table->thinker_num, sizeof(pthread_mutex_t));
	if (!table->forks)
		return ;
	while (++i)
		pthread_mutex_init(&table->forks[i], NULL);
	pthread_mutex_init(&table->food_status, NULL);	
	pthread_mutex_init(&table->life_status, NULL);	
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->meal_num = ft_atoi(av[5]);
	else
		table->meal_num = -1;	
	table->first_thought = NULL;
	table->last_thought = NULL;
}

t_thinker *ft_add_back(t_table *table, uint64_t i)
{
	t_thinker	*new_idea;
	
	new_idea = ft_calloc(1, sizeof(t_thinker));
	if (!new_idea)
		return (NULL);
	new_idea->table = table;
	new_idea->id = i;
	new_idea->meal_count = 0;
	if (!table->first_thought)
	{
		table->first_thought = new_idea;
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

void	join_thinkers(t_table *table)
{
	t_thinker	*current;

	current = table->first_thought;
	while (current)
	{
		pthread_join(current->idea, NULL);
		current = current->next;
	}
}

void	destroy_and_free(t_table *table)
{
	uint64_t	i;

	i = 0;
	while (i < table->thinker_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
