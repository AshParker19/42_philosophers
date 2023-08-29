/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/29 23:25:02 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thinking_process(void *arg)
{
	t_thinker	*thinker;
	
	thinker = (t_thinker *)arg;
	// while (1)
	// {
	// 	eat();
	// 	save last_meal_time;
	// 	sleep();
	// 	think;
	// }
	while (1)
	{
		// pthread_mutex_lock(&thinker->table->forks[thinker->thinker_id]);
		
		// pthread_mutex_unlock(&thinker->table->forks[thinker->thinker_id]);
		// if (thinker == false)
		// {
		// 	pthread_mutex_lock(&thinker->table->forks[thinker->thinker_id]);
		// 	printf ("%lu %d has taken a fork\n", get_current_time() - thinker->table->start_time, thinker->thinker_id);
		// 	pthread_mutex_unlock(&thinker->table->forks[thinker->thinker_id]);
		// }
		// if (thinker->next && thinker->next == false)
		// {
		// 	pthread_mutex_lock(&thinker->table->forks[thinker->thinker_id]);
		// 	printf ("%lu %d has taken a fork\n", get_current_time() - thinker->table->start_time, thinker->thinker_id);
		// 	pthread_mutex_unlock(&thinker->table->forks[thinker->thinker_id]);
		// }		
	}
	return (NULL);
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
			if (get_current_time() - current->last_meal >= table->time_to_die)
			{
				printf ("%lu %d died\n", get_current_time() - table->start_time, current->thinker_id);
				table->sage_word = true;
				break;
			}
			current = current->next;
		}
		ft_usleep(10000);
	}
	return (NULL);
}

void	organize_table(t_table *table)
{
	static uint64_t	i;
	t_thinker		*current;

	while (i < table->thinker_num)
		table->first_thought = ft_add_back(table, i++);
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
	table_init(&table, av);
	organize_table(&table);
}

