/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/02 18:57:07 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	existence_phase(t_thinker *thinker, bool fork_status);

void	log_action(t_thinker *thinker, char *action)
{
	uint64_t	timestamp;

	timestamp = get_current_time() - thinker->table->start_time;
	// pthread_mutex_lock(&thinker->table->forks[thinker->id - 1]);
	printf (CYAN"[ %ld ]\t   " GREEN"%d\t " RESET"%s"RESET,
		timestamp, thinker->id, action);
	// pthread_mutex_unlock(&thinker->table->forks[thinker->id - 1]);
}

void	pick_up_forks(t_thinker *thinker)
{
	pthread_mutex_lock(&thinker->table->forks[thinker->id - 1]);
	log_action(thinker, FORK);	
	if (thinker->id == (int)thinker->table->thinker_num)
		pthread_mutex_lock(&thinker->table->forks[0]);
	else
		pthread_mutex_lock(&thinker->table->forks[thinker->id]);
	log_action(thinker, FORK);
	existence_phase(thinker, true);
}

void	eat(t_thinker *thinker)
{
	ft_usleep(thinker->table->time_to_eat);
	log_action(thinker, EAT);
	thinker->last_meal = get_current_time();
	thinker->meal_count++;
}

void	put_down_forks(t_thinker *thinker)
{
	pthread_mutex_unlock(&thinker->table->forks[thinker->id - 1]);
	if (thinker->id == (int)thinker->table->thinker_num)
		pthread_mutex_unlock(&thinker->table->forks[0]);
	else	
		pthread_mutex_unlock(&thinker->table->forks[thinker->id]);
}

void	my_sleep(t_thinker *thinker)
{
	ft_usleep(thinker->table->time_to_sleep);
	log_action(thinker, SLEEP);
}

void	think(t_thinker *thinker)
{
	uint64_t	wake_up_time;

	wake_up_time = get_current_time() - thinker->last_meal;
	ft_usleep(wake_up_time);
	log_action(thinker, THINK);
}

void	existence_phase(t_thinker *thinker, bool fork_status)
{
	// eat only if 2 forks
	eat(thinker);
	if (fork_status == true)
		put_down_forks(thinker);
	my_sleep(thinker);
	think(thinker);
}

void	*thinking_process(void *arg)
{
	t_thinker	*thinker;
	
	thinker = (t_thinker *)arg;
	while (!thinker->table->dead)
	{
		if (thinker->id % 2 == 0)
			pick_up_forks(thinker);
		else
			existence_phase(thinker, false);
		if (thinker->table->dead == true)
			break;	
	}
	return (NULL);
} 

// get_current_time() - current->last_meal >= table->time_to_die
// get_current_time() - table->start_time, current->id

void	death_check(t_table *table)
{
	t_thinker	*current;
	uint64_t	current_time;

	while (!table->dead)
	{
		current = table->first_thought;
		while (current)
		{
			current_time = get_current_time() - current->last_meal;
			if (current_time >= table->time_to_die)
			{
				// pthread_mutex_unlock(&table->forks[current->id - 1]);
				// if (current->id == (int)table->thinker_num)
				// 	pthread_mutex_unlock(&table->forks[0]);
				// else
				// 	pthread_mutex_unlock(&table->forks[current->id]);	
				table->dead = true;
				log_action(current, DIE);
				break ;
			}
			current = current->next;
		}
	}
}

void	organize_table(t_table *table)
{
	uint64_t		i;
	t_thinker		*current;

	i = 1;
	while (i <= table->thinker_num)
		table->first_thought = ft_add_back(table, i++);
	if (table->thinker_num == 1)
	{
		log_action(table->first_thought, FORK);
		ft_usleep(table->time_to_die);
		log_action(table->first_thought, DIE);
		table->dead = true;
		return ;
	}	
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

