/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:27:08 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/19 18:00:40 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*take_a_fork(void *thinker)
{
	t_table *mind;

	mind = (t_table *)thinker;
	pthread_mutex_lock(&mind->lock);
	printf ("%zu has taken a fork\n", mind->thinker_counter);
	mind->thinker_counter++;
	pthread_mutex_unlock(&mind->lock);
	return (NULL);
}

