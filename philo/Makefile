NAME = philo

CC = cc

CFLAGS = -pthread  -Wall -Werror -Wextra -g
#TODO:FIXME: FUCKING FLAGS!!! FIXME:TODO:

SRCS := $(wildcard *.c)

OBJS :=$(SRCS:.c=.o)

# colors
RED    = 	\033[0;31m
GREEN  = 	\033[0;32m
ORANGE = 	\033[0;33m
BLUE   = 	\033[34m
PURPLE = 	\033[35m
RESET  = 	\033[0m

###############################################################

.PHONY: all clean fclean re

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@rm -f $(OBJS) #TODO:FIXME: REMOVE THIS SHIT!!! FIXME:TODO:
	@echo "$(ORANGE)♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖"
	@echo "$(ORANGE)♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙"
	@echo "$(PURPLE)♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙"
	@echo "$(PURPLE)♜ ♞ ♝ ♚ ♛ ♝ ♞ ♜$(RESET)"


%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all
