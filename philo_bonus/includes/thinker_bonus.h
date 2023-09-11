/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:04 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/11 02:18:58 by anshovah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THINKER_BONUS_H
# define THINKER_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <sys/time.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

/* colors for action logs */
# define GREEN 			"\033[0;32m"
# define RED 			"\033[0;31m"
# define YELLOW 		"\x1b[33m"
# define CYAN 			"\x1b[36m"
# define RESET 			"\033[0m"

/* action logs */
# define FORK			"\x1b[33mhas taken a fork\033[0m"
# define EAT			"\x1b[35mis eating\033[0m"
# define SLEEP			"\x1b[34mis sleeping\033[0m"
# define THINK			"\033[38;5;203mis thinking\033[0m"
# define DIE			"\033[0;31mdied\033[0m"

/* errors */
# define PARSING_ERROR	1
# define INIT_ERROR		2

struct	s_table;

/* each thinker is the node of the linked list */
typedef struct s_thinker
{
	pid_t				idea;
	int					id;
	int					meal_count;
	uint64_t			last_meal;
	struct s_table		*table;
	struct s_thinker	*next;
}				t_thinker;

/* table with all the info  */
typedef struct	s_table
{
	int		ac;
	bool	dead;
	sem_t			*forks;
	sem_t			*lock;
	sem_t			*key;
	uint64_t		thinker_num;
	uint64_t		start_time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				meal_num;
	t_thinker		*first_thought;
	t_thinker		*last_thought;
}				t_table;

/* parsing */
int			parser(int ac, char **av);
size_t		ft_strlen(const char *s);
uint64_t	ft_atoi(const char *nptr);

/* utils */
void		*ft_calloc(size_t nmemb, size_t size);
void		ft_bzero(void *s, size_t n);
uint64_t	get_current_time(void);
void		ft_usleep(uint64_t time);

/* thinking process */
void		organize_table(t_table *table);

/* thinker utils */
int			table_init(t_table *table, int ac, char **av, int i);
t_thinker	*ft_add_back(t_table *table, uint64_t i);


#endif