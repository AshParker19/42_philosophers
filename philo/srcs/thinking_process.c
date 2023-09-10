/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/10 00:19:54 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker.h"

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
		pthread_create(&current->idea, NULL, thinking_process, current);
		current = current->next;
	}
	if (table->thinker_num > 1)
		death_check(table);
	join_thinkers(table);
	destroy_and_free(table);
}

void	*thinking_process(void *arg)
{
	t_thinker	*thinker;

	thinker = (t_thinker *)arg;
	if (thinker->table->thinker_num == 1)
	{
		one_thinker(thinker->table->time_to_die);
		return (NULL);
	}
	if (thinker->id % 2)
		ft_usleep(10);
	existence(thinker);
	return (NULL);
}

void	existence(t_thinker *thinker)
{
	while (1)
	{
		pthread_mutex_lock(&thinker->table->key);
		if (thinker->table->dead)
		{
			pthread_mutex_unlock(&thinker->table->key);
			break ;
		}
		pthread_mutex_unlock(&thinker->table->key);
		pick_up_forks(thinker);
		eat(thinker);
		put_down_forks(thinker);
		ft_usleep(thinker->table->time_to_sleep);
		log_action(thinker, THINK);
		usleep(50);
		pthread_mutex_lock(&thinker->lock);
		if (thinker->meal_count != -1
			&& thinker->meal_count == thinker->table->meal_num)
		{
			pthread_mutex_unlock(&thinker->lock);
			break ;
		}
		pthread_mutex_unlock(&thinker->lock);
	}
}

void	death_check(t_table *table)
{
	t_thinker	*current;
	uint64_t	all_ate;

	while (!table->dead)
	{
		pthread_mutex_lock(&table->key);
		current = table->first_thought;
		pthread_mutex_unlock(&table->key);
		all_ate = 0;
		while (current)
		{
			pthread_mutex_lock(&current->lock);
			check_death_condition(table, current, &all_ate);
			pthread_mutex_unlock(&current->lock);
			current = current->next;
		}
		pthread_mutex_lock(&table->key);
		if (all_ate == table->thinker_num)
		{
			table->dead = true;
			pthread_mutex_unlock(&table->key);
			break ;
		}
		pthread_mutex_unlock(&table->key);
	}
}

void	check_death_condition(t_table *table, t_thinker *current, uint64_t *ate)
{
	uint64_t	now;

	now = get_current_time() - table->start_time;
	if (table->dead == true)
		return ;
	if (now >= (current->last_meal - table->start_time)
		+ table->time_to_die && (table->meal_num == -1
			|| current->meal_count < table->meal_num))
	{
		die(table, current, get_current_time()
			- current->table->start_time);
	}
	else if (table->meal_num != -1
		&& current->meal_count == table->meal_num)
	{
		pthread_mutex_lock(&table->key);
		*ate = *ate + 1;
		pthread_mutex_unlock(&table->key);
	}
}
