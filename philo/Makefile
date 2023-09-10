#################################################################################################
###**										philosophers									**###
#####***************************************************************************************#####

###-------------------------------------------------------------------------------------------###
###**							Variables and dependencies									**###
#####---------------------------------------------------------------------------------------#####

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -pthread -fsanitize=thread 

SRCS := srcs/actions.c	srcs/parsing.c	srcs/thinker.c		\
		srcs/thinking_process.c srcs/thoughts.c srcs/utils.c

INCLUDES = includes

OBJS_DIR = objs

OBJS :=$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#

# colors
RED    = 	\033[0;31m
GREEN  = 	\033[0;32m
ORANGE = 	\033[0;33m
BLUE   = 	\033[34m
PURPLE = 	\033[35m
RESET  = 	\033[0m

###+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++###
###**								PHONY targets and rules									**###
#####+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#####

.PHONY: all clean fclean norm re

all : $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BLUE)  ┓ •┓       ┓        "
	@echo "$(BLUE)┏┓┣┓┓┃┏┓┏┏┓┏┓┣┓┏┓┏┓┏┓┏"
	@echo "$(PURPLE)┣┛┛┗┗┗┗┛┛┗┛┣┛┛┗┗ ┛ ┗ ┛"
	@echo "$(PURPLE)┛          ┛          $(RESET)"

$(OBJS_DIR)/srcs:
	@mkdir -p $(OBJS_DIR)/srcs
	
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)/srcs
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(BLUE)┌────────────────────┐"
	@echo "│    $(ORANGE)[✓] CLEANED!$(BLUE)    │"
	@echo "$(BLUE)└────────────────────┘$(RESET)"

fclean : clean
	@rm -f $(NAME)

norm : 
	@echo "$(ORANGE)******************************$(GREEN)"
	@echo "$(BLUE)      CHECK SOURSE FILES$(RESET)"
	@echo "$(ORANGE)******************************$(GREEN)"
	@norminette $(SRCS)
	@echo "$(ORANGE)******************************$(GREEN)"
	@echo "$(BLUE)        CHECK INCLUDES$(RESET)"
	@echo "$(ORANGE)******************************$(GREEN)"
	@norminette $(INCLUDES)
	@echo "$(ORANGE)******************************$(BLUE)"
	@echo "        NO NORM ERRORS$(RESET)"
	@echo "$(ORANGE)******************************$(DEF)"

re : fclean all


#####***************************************************************************************#####
###**										Good luck!										**###
#################################################################################################