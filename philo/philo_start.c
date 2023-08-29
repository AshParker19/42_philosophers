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
	table->sage_word = false;
	table->start_time = get_current_time();
	table->first_thought = NULL;
	table->last_thought = NULL;
}

void	*thinking_process(void *arg)
{
	t_thinker	*thinker;
	
	thinker = (t_thinker *)arg;

	while (!thinker->table->sage_word)
	{
		pthread_mutex_lock(&thinker->fork);
		if (thinker->first == true)
		{
			thinker->free_fork = true;
			printf ("%lu %d has taken a fork\n", get_current_time() - thinker->table->start_time, thinker->thinker_id);
			if (thinker->free_fork == true && thinker->table->last_thought->free_fork == true)
				printf ("%lu %d has taken a fork\n", get_current_time() - thinker->table->start_time, thinker->thinker_id);
			printf ("%lu %d is eating\n", get_current_time() - thinker->table->start_time, thinker->thinker_id);
		}
		thinker->last_meal = get_current_time();
		thinker->meal_count++;
		pthread_mutex_unlock(&thinker->fork);
		printf ("%lu %d is sleeping\n", get_current_time() - thinker->table->start_time, thinker->thinker_id);
		printf ("%lu %d is thinking\n", get_current_time() - thinker->table->start_time, thinker->thinker_id);
		ft_usleep(ft_atoi(thinker->table->av[3]));
	}
	return (NULL);
}

// if (current_time - last_meal_time >= time_to_die)
// 	die();

t_thinker *ft_add_back(t_table *table, int i)
{
	t_thinker	*new_idea;
	
	new_idea = malloc(1 * sizeof(t_thinker));
	if (!new_idea)
		return (NULL);
	new_idea->free_fork = false;
	new_idea->table = table;
	new_idea->thinker_id = i;
	pthread_mutex_init(&new_idea->fork, NULL);
	if (!table->first_thought)
	{
		table->first_thought = new_idea;
		table->last_thought = new_idea;
		new_idea->first = true;
		return (new_idea);
	}
	else
	{
		table->last_thought->next = new_idea;
		table->last_thought = new_idea;
		return (table->first_thought);
	}
}

void*	sage_supervision(void *arg)
{
	t_table		*table;
	t_thinker	*current;

	table = (t_table *)arg;
	while (!table->sage_word)
	{
		current = table->first_thought;
		while (current)
		{
			if (get_current_time() - current->last_meal >= ft_atoi(current->table->av[2]))
			{
				printf ("%lu %d died\n", get_current_time() - table->start_time, current->thinker_id);
				table->sage_word = true;
				break;
			}
			current = current->next;
		}
	}
	return (NULL);
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
	t_thinker	*current;

	current = table->first_thought;
	while (current)
	{
		pthread_mutex_destroy(&current->fork);
		current = current->next;
	}
}

void	organize_table(t_table *table)
{
	static uint64_t	i;
	t_thinker		*current;

	while (i++ < ft_atoi(table->av[1]))
		table->first_thought = ft_add_back(table, i);
	table->last_thought->last = true;	
	current = table->first_thought;
	while (current)
	{
		pthread_create(&current->idea, NULL, thinking_process, current);
		current = current->next;
	}
	pthread_create(&table->sage, NULL, sage_supervision, table);
	join_thinkers(table);
	pthread_join(table->sage, NULL);
	destroy_and_free(table);
}

int main(int ac, char *av[])
{
	t_table table;

	if (!parser(ac, av))
		return (1);
	table_init(&table, ac, av);
	organize_table(&table);
}

