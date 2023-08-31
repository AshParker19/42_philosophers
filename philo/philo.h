/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:25 by anshovah          #+#    #+#             */
/*   Updated: 2023/08/31 23:19:19 by anshovah         ###   ########.fr       */
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

/* action logs */
# define FORK	"has taken a fork\n"
# define EAT	"is eating\n"
# define SLEEP	"is sleeping\n"
# define THINK	"is thinking\n"
# define DIE	"died\n"	

struct s_table;
/* each thinker is the node of the linked list */
typedef struct s_thinker
{	
	pthread_t 			idea;
	int 				id;
	int					meal_count;
	uint64_t			last_meal;
	struct s_table		*table;
	struct s_thinker 	*next;
}				t_thinker;

/* table with all the info  */
typedef struct s_table
{
	int				ac;
	pthread_mutex_t	*forks;
	uint64_t		thinker_num;
	uint64_t		start_time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	uint64_t		meal_num;
	t_thinker		*first_thought;
	t_thinker		*last_thought;
}				t_table;


/* parsing */
int		parser(int ac, char **av);

/* philo utils */
void		table_init(t_table *table, int ac, char **av, int i);
t_thinker 	*ft_add_back(t_table *table, int i);
void		join_thinkers(t_table *table);
void		destroy_and_free(t_table *table);

/* utils */
size_t		ft_strlen(const char *s);
uint64_t 	ft_atoi(const char *nptr);
uint64_t	get_current_time(void);
int			ft_usleep(size_t ms);

#endif