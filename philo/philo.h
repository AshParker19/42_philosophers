/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:08:25 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/03 16:23:56 by anshovah         ###   ########.fr       */
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

/* colors for action logs */
// # define GREEN 			"\033[0;32m"
// # define B_WHITE		"\x1b[37;101m"
// # define RED 			"\033[0;31;47m"
// # define YELLOW 		"\x1b[33;45m"
// # define CYAN 			"\x1b[36m"
// # define PURPLE 		"\x1b[35;106m"
// # define BLUE			"\x1b[34;43m"
// # define RESET 			"\033[0m"

# define GREEN 			"\033[0;32m"
# define B_WHITE		"\x1b[37m"
# define RED 			"\033[0;31m"
# define YELLOW 		"\x1b[33m"
# define CYAN 			"\x1b[36m"
# define PURPLE 		"\x1b[35m"
# define BLUE			"\x1b[34m"
# define RESET 			"\033[0m"

/* action logs */
# define FORK	YELLOW"has taken a fork"RESET
# define EAT	PURPLE"is eating"RESET
# define SLEEP	BLUE"is sleeping"RESET
# define THINK	B_WHITE"is thinking"RESET
# define DIE	RED"died"RESET

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
	bool			dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
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
t_thinker 	*ft_add_back(t_table *table, uint64_t  i);
void		join_thinkers(t_table *table);
void		destroy_and_free(t_table *table);

/* utils */
size_t		ft_strlen(const char *s);
uint64_t 	ft_atoi(const char *nptr);
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
uint64_t	get_current_time(void);
int			ft_usleep(size_t ms);

#endif