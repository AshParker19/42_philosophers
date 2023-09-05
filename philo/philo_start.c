/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/05 20:17:38 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_time(uint64_t time)
{
	uint64_t	start;
	uint64_t	now;

	start = get_current_time();
	while (1)
	{
		now = get_current_time();
		if (now - start >= time)
			break ;
		usleep(100);
	}
}

void	log_action(t_thinker *thinker, char *action)
{
	uint64_t	timestamp;
	
	pthread_mutex_lock(&thinker->table->key);
	if (!thinker->table->dead)
	{
		timestamp = get_current_time() - thinker->table->start_time;
		printf (CYAN"%ld\t" GREEN"%d\t" RESET"%s\n",
			timestamp, thinker->id, action);
	}
	pthread_mutex_unlock(&thinker->table->key);
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
	pthread_mutex_lock(&thinker->lock);
	thinker->last_meal = get_current_time();
	pthread_mutex_unlock(&thinker->lock);
	thinker->meal_count++;
	log_action(thinker, EAT);
	log_action(thinker, SLEEP);
	sleep_time(thinker->table->time_to_eat);
}

void	put_down_forks(t_thinker *thinker)
{
	pthread_mutex_unlock(&thinker->table->forks[thinker->id - 1]);
	if (thinker->id == (int)thinker->table->thinker_num)
		pthread_mutex_unlock(&thinker->table->forks[0]);
	else	
		pthread_mutex_unlock(&thinker->table->forks[thinker->id]);
}

void	existence(t_thinker *thinker)
{
	bool	temp;

	while (!thinker->table->dead)
	{
		pthread_mutex_lock(&thinker->table->key);
		temp = thinker->table->dead;
		pthread_mutex_unlock(&thinker->table->key);
		pick_up_forks(thinker);
		eat(thinker);
		put_down_forks(thinker);
		sleep_time(thinker->table->time_to_sleep);
		log_action(thinker, THINK);
	}
}

void	*thinking_process(void *arg)
{
	t_thinker	*thinker;
	
	thinker = (t_thinker *)arg;
	if (thinker->id % 2)
		ft_usleep(thinker->table->thinker_num);
	existence(thinker);
	return (NULL);
} 

void	death_check(t_table *table)
{
	t_thinker	*current;
	uint64_t	now;
	uint64_t	timestamp;

	while (!table->dead)
	{
		pthread_mutex_lock(&table->key);
		current = table->first_thought;
		pthread_mutex_unlock(&table->key);
		while (current)
		{
			pthread_mutex_lock(&current->lock);
			now = get_current_time() - table->start_time;
			if (now >= current->last_meal + table->time_to_die)
			{
				timestamp = get_current_time() - current->table->start_time;
				printf (CYAN"%ld\t" GREEN"%d\t" RESET"%s\n",
				timestamp, current->id, "\033[0;31mdied\033[0m");
				pthread_mutex_lock(&table->key);
				table->dead = true;
				pthread_mutex_unlock(&table->key);
				pthread_mutex_unlock(&current->lock);
				break ;
			}
			pthread_mutex_unlock(&current->lock);
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
