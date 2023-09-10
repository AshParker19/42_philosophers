/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anshovah <anshovah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 19:02:04 by anshovah          #+#    #+#             */
/*   Updated: 2023/09/10 19:15:56 by anshovah         ###   ########.fr       */
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
typedef struct t_thinker
{
	pid_t		idea;
	int			id;
	int			meal_count;
	uint64_t	last_meal;
	
}

#endif