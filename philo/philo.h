/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:25 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/21 17:13:18 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdint.h>
#include <pthread.h>

struct s_table;
/* each thinker is the node of the linked list */
typedef struct s_thinker
{	
	pthread_t 			idea;
	pthread_mutex_t		fork;
	bool				free_fork;
	int 				thinker_id;
	int					meal_count;
	uint64_t			last_meal;
	bool				first;
	bool				last;
	struct s_table		*table;
	struct s_thinker 	*next;
}				t_thinker;

/* table with all the info  */
typedef struct s_table
{
	int 			ac;
	char 			**av;
	pthread_t		sage;
	bool			sage_word;
	bool			dead_mf;
	uint64_t		start_time;
	t_thinker		*first_thought;
	t_thinker		*last_thought;
}				t_table;


/* parsing */
int		parser(int ac, char **av);

/* routines */


/* utils */
size_t		ft_strlen(const char *s);
uint64_t 	ft_atoi(const char *nptr);
uint64_t	get_current_time(void);
int			ft_usleep(size_t ms);

#endif