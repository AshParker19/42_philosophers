/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:25 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/19 17:53:58 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <pthread.h>

// another struct for each philo linked list

typedef struct s_thinker
{
	pthread_t 			thought;
	bool				lock_status;
	struct s_thinker 	*next;
	struct s_thinker 	*prev;
}				t_thinker;

typedef struct s_table
{
	int 			ac;
	char 			**av;
	pthread_mutex_t	lock;
	size_t			thinker_counter;
	t_thinker		*thinker;
	t_thinker		*last_thought;
}				t_table;


/* parsing */
int		parser(char **av);

/* routines */
void	*take_a_fork(void *thinker);

/* utils */
size_t		ft_strlen(const char *s);
long int	ft_atoi(const char *nptr);

#endif