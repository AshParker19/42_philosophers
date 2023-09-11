/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thoughts_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 01:10:19 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/11 02:42:56 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker_bonus.h"

int	table_init(t_table *table, int ac, char **av, int i)
{
	table->ac = ac;
	table->dead = false;
	table->start_time = get_current_time();
	table->thinker_num = ft_atoi(av[1]);
	table->forks = sem_open("/forks", O_CREAT, 0666, table->thinker_num);
	table->lock = sem_open("/lock", O_CREAT, 0666, 1);
	table->key = sem_open("/key", O_CREAT, 0666, 1);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->meal_num = ft_atoi(av[5]);
	else
		table->meal_num = -1;
	table->first_thought = NULL;
	table->last_thought = NULL;
	return (1);
}

t_thinker	*ft_add_back(t_table *table, uint64_t i)
{
	t_thinker	*new_idea;

	new_idea = ft_calloc(1, sizeof(t_thinker));
	if (!new_idea)
		return (NULL);
	new_idea->table = table;
	new_idea->id = i;
	new_idea->meal_count = 0;
	new_idea->last_meal = 0;
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

void	log_action(t_thinker *thinker, char *action)
{
	uint64_t	timestamp;

	// pthread_mutex_lock(&thinker->table->key);
	if (!thinker->table->dead)
	{
		timestamp = get_current_time() - thinker->table->start_time;
		printf (CYAN"%ld\t" GREEN"%d\t" RESET"%s\n",
			timestamp, thinker->id, action);
	}
	// pthread_mutex_unlock(&thinker->table->key);
}

void	wait_thinkers(t_table *table) //wait
{
	t_thinker	*current;

	current = table->first_thought;
	while (current)
	{
		// pthread_join(current->idea, NULL);
		current = current->next;
	}
}

void	close_and_free(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->lock);
	sem_close(table->key);
	sem_unlink("/forks");
	sem_unlink("/lock");
	sem_unlink("/key");
}