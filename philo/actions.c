/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:59:48 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/09 21:17:01 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thinker.h"

void	one_thinker(uint64_t time)
{
	printf (CYAN"0\t" GREEN"1\t" YELLOW"has taken a fork\n" RESET);
	ft_usleep(time);
	printf (CYAN"%lu\t" GREEN"1\t" RED"died\n" RESET, time);
}

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

void	die(t_table *table, t_thinker *current, uint64_t timestamp)
{
	pthread_mutex_lock(&table->key);
	table->dead = true;
	pthread_mutex_unlock(&table->key);
	printf (CYAN"%ld\t" GREEN"%d\t" RED"%s\n"RESET,
		timestamp, current->id, "died");
}
