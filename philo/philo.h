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
#include <pthread.h>

/* each thinker is the node of the linked list */
typedef struct s_thinker
{	
	pthread_t 			idea;
	pthread_mutex_t		lock;
	bool				lock_status;
	struct s_thinker 	*next;
}				t_thinker;

/* table with all the info  */
typedef struct s_table
{
	int 			ac;
	char 			**av;
	size_t			thinker_counter;
	t_thinker		*first_thought;
	t_thinker		*last_thought;
}				t_table;


/* parsing */
int		parser(char **av);

/* routines */


/* utils */
size_t		ft_strlen(const char *s);
long int	ft_atoi(const char *nptr);
size_t		get_current_time(void);
int			ft_usleep(useconds_t ms);

#endif