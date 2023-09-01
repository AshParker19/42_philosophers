/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/01 01:18:39 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_action(t_thinker *thinker, char *action)
{
	uint64_t	timestamp;

	timestamp = get_current_time() - thinker->table->start_time;
	printf ("%ld %d %s\n", timestamp, thinker->id, action);
}

void	pick_up_forks(t_thinker *thinker, bool *dead)
{
	if (thinker->table->thinker_num == 1)
	{
		ft_usleep(thinker->table->time_to_die);
		log_action(thinker, DIE);
		*dead = true;
		return ;
	}
	pthread_mutex_lock(&thinker->table->forks[thinker->id - 1]);
	log_action(thinker, FORK);	
	if (thinker->id == (int)thinker->table->thinker_num - 1)
		pthread_mutex_lock(&thinker->table->forks[0]);
	else	
		pthread_mutex_lock(&thinker->table->forks[thinker->id + 1]);
	log_action(thinker, FORK);
	existence_phase(thinker, dead, true);
}

void	eat(t_thinker *thinker, bool *dead)
{
	ft_usleep(thinker->table->time_to_eat);
	thinker->last_meal = get_current_time();
	thinker->meal_count++;
}

void	put_down_forks(t_thinker *thinker)
{
	pthread_mutex_unlock(&thinker->table->forks[thinker->id - 1]);
	if (thinker->id == (int)thinker->table->thinker_num - 1)
		pthread_mutex_unlock(&thinker->table->forks[0]);
	else	
		pthread_mutex_unlock(&thinker->table->forks[thinker->id + 1]);
}

void	my_sleep(t_thinker *thinker)
{
	ft_usleep(thinker->table->time_to_sleep);
	log_action(thinker, SLEEP);
}

void	think(t_thinker *thinker)
{

}

void	existence_phase(t_thinker *thinker, bool *dead, bool fork_status)
{
	eat(thinker, dead);
	if (fork_status == true)
		put_down_forks(thinker);
	my_sleep(thinker);
	think(thinker);
}

void	*thinking_process(void *arg)
{
	t_thinker	*thinker;
	bool		dead;
	
	dead = false;
	thinker = (t_thinker *)arg;
	while (1)
	{
		if (thinker->id % 2 == 0)
			pick_up_forks(thinker, &dead);
		else
			existence_phase(thinker, &dead, false);
		if (dead == true)
			break;	
	}
	return (NULL);
}

// get_current_time() - current->last_meal >= table->time_to_die
// get_current_time() - table->start_time, current->id

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
	death_check(table);
	join_thinkers(table);
	destroy_and_free(table);
}

int main(int ac, char *av[])
{
	t_table table;

	if (!parser(ac, av))
		return (1);
	table_init(&table, ac, av, -1);
	organize_table(&table);
}

