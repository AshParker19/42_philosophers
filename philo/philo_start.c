/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:05 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/07 17:33:29 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_up_forks(t_thinker *thinker)
{
	int	left_fork;
	int	right_fork;

	if (thinker->id % 2 == 0)
	{
		left_fork = thinker->id - 1;
		right_fork = thinker->id % thinker->table->thinker_num;
	}
	else
	{
		left_fork = thinker->id % thinker->table->thinker_num;
		right_fork = thinker->id - 1;
	}
	pthread_mutex_lock(&thinker->table->forks[left_fork]);
	pthread_mutex_lock(&thinker->table->forks[right_fork]);
	log_action(thinker, FORK);	
	log_action(thinker, FORK);	
}

void	eat(t_thinker *thinker)
{
	pthread_mutex_lock(&thinker->lock);
	thinker->last_meal = get_current_time();
	thinker->meal_count++;
	pthread_mutex_unlock(&thinker->lock);
	log_action(thinker, EAT);
	ft_usleep(thinker->table->time_to_eat);
	log_action(thinker, SLEEP);
}

void	put_down_forks(t_thinker *thinker)
{
	if (thinker->id == (int)thinker->table->thinker_num)
		pthread_mutex_unlock(&thinker->table->forks[0]);
	else	
		pthread_mutex_unlock(&thinker->table->forks[thinker->id]);
	pthread_mutex_unlock(&thinker->table->forks[thinker->id - 1]);
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
		if (thinker->meal_count != -1 && thinker->meal_count == thinker->table->meal_num)
		{
			pthread_mutex_unlock(&thinker->lock);
			break ;
		}
		pthread_mutex_unlock(&thinker->lock);
	}
}

void	*thinking_process(void *arg)
{
	t_thinker	*thinker;
	
	thinker = (t_thinker *)arg;
	if (thinker->id % 2)
		ft_usleep(10);
	existence(thinker);
	return (NULL);
} 

void	death_check(t_table *table)
{
	t_thinker	*current;
	uint64_t	now;
	uint64_t	timestamp;
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
			now = get_current_time() - table->start_time;
			if (now >= (current->last_meal - table->start_time) + table->time_to_die
				&& (table->meal_num == -1 || current->meal_count < table->meal_num))
			{
				timestamp = get_current_time() - current->table->start_time;
				printf (CYAN"%ld\t" GREEN"%d\t%s\n",
				timestamp, current->id, "\033[0;31mdied\033[0m");
				pthread_mutex_lock(&table->key);
				table->dead = true;
				pthread_mutex_unlock(&table->key);
				pthread_mutex_unlock(&current->lock);
				break ;
			}
			else if (table->meal_num != -1 && current->meal_count == table->meal_num)
				all_ate++;
			pthread_mutex_unlock(&current->lock);
			current = current->next;
		}
		if (all_ate == table->thinker_num)
			break ;
	}
}

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
	death_check(table);
	join_thinkers(table);
	destroy_and_free(table);
}

int	one_thinker(uint64_t time)
{
	printf (CYAN"0\t" GREEN"1\t" YELLOW"has taken a fork\n" RESET);
	printf (CYAN"%lu\t" GREEN"1\t" RED"died\n" RESET, time);
	return (0);
}

int main(int ac, char *av[])
{
	t_table table;

	if (!parser(ac, av))
		return (1);
	if (ft_atoi(av[1]) == 1)
		return (one_thinker(ft_atoi(av[2])));	
	table_init(&table, ac, av, -1);
	organize_table(&table);
}
