/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/03 20:11:34 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(t_thinker *thinker, time_t time)
{
	(void)thinker;
	time_t	start;
	time_t	now;

	start = get_current_time();
	while (1)
	{
		now = get_current_time();
		if (now - start >= time)
			break ;
		usleep(100);
	}
}
void	existence_phase(t_thinker *thinker, bool fork_status);

void	log_action(t_thinker *thinker, char *action)
{
	uint64_t	timestamp;
	
	pthread_mutex_lock(&thinker->table->print);
	if (!thinker->table->dead)
	{
		timestamp = get_current_time() - thinker->table->start_time;
		printf (CYAN"%ld\t" GREEN"%d\t" RESET"%s\n",
			timestamp, thinker->id, action);
	}
	pthread_mutex_unlock(&thinker->table->print);
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
}

void	eat(t_thinker *thinker)
{
	thinker->last_meal = get_current_time();
	thinker->meal_count++;
	log_action(thinker, EAT);
	my_sleep(thinker, thinker->table->time_to_eat);
}

void	put_down_forks(t_thinker *thinker)
{
	pthread_mutex_unlock(&thinker->table->forks[thinker->id - 1]);
	if (thinker->id == (int)thinker->table->thinker_num)
		pthread_mutex_unlock(&thinker->table->forks[0]);
	else	
		pthread_mutex_unlock(&thinker->table->forks[thinker->id]);
}


void	think(t_thinker *thinker)
{
	log_action(thinker, THINK);
}

void	existence_phase(t_thinker *thinker, bool fork_status)
{
	(void)fork_status;
	while (!thinker->table->dead)
	{
		pick_up_forks(thinker);
		eat(thinker);
		put_down_forks(thinker);
		my_sleep(thinker, thinker->table->time_to_sleep);
		log_action(thinker, EAT);
		think(thinker);
	}
}

void	*thinking_process(void *arg)
{
	t_thinker	*thinker;
	
	thinker = (t_thinker *)arg;
	if (thinker->id % 2)
		ft_usleep(thinker->table->thinker_num);
	existence_phase(thinker, 0);
	return (NULL);
} 

// get_current_time() - current->last_meal >= table->time_to_die
// get_current_time() - table->start_time, current->id

void	death_check(t_table *table)
{
	t_thinker	*current;
	uint64_t	now;
	uint64_t	timestamp;

	while (!table->dead)
	{
		current = table->first_thought;
		while (current)
		{
			now = get_current_time() - current->table->start_time;
			if (now >= current->last_meal + table->time_to_die)
			{
				timestamp = get_current_time() - current->table->start_time;
				printf (CYAN"%ld\t" GREEN"%d\t" RESET"%s\n",
				timestamp, current->id, "\033[0;31mdied");
				table->dead = true;
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

