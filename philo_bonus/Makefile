#################################################################################################
###**									philosophers bonus									**###
#####***************************************************************************************#####

###-------------------------------------------------------------------------------------------###
###**								Variables and dependencies								**###
#####---------------------------------------------------------------------------------------#####

NAME = philo_bonus

CC = cc

CFLAGS = -g -pthread #-fsanitize=address #-Wall -Werror -Wextra 
										#TODO:FIXME: FLAGS!!! #FIXME:TODO:
SRCS := $(wildcard srcs/*.c)

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
	@echo "$(BLUE)  ┓ •┓       ┓        $(ORANGE)  ┓        "
	@echo "$(BLUE)┏┓┣┓┓┃┏┓┏┏┓┏┓┣┓┏┓┏┓┏┓┏$(ORANGE)  ┣┓┏┓┏┓┓┏┏"
	@echo "$(PURPLE)┣┛┛┗┗┗┗┛┛┗┛┣┛┛┗┗ ┛ ┗ ┛$(GREEN)  ┗┛┗┛┛┗┗┛┛"
	@echo "$(PURPLE)┛          ┛                      $(RESET)"

$(OBJS_DIR)/srcs:
	@mkdir -p $(OBJS_DIR)/srcs
	
$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)/srcs
	@$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(BLUE)┌────────────────────────────────┐"
	@echo "│          $(ORANGE)[✓] CLEANED!$(BLUE)          │"
	@echo "$(BLUE)└────────────────────────────────┘$(RESET)"

fclean : clean
	@rm -f $(NAME)

norm : 
	@echo "$(ORANGE)******************************"
	@echo "$(BLUE)      CHECK SOURSE FILES$(RESET)"
	@echo "$(ORANGE)******************************$(PURPLE)"
	@norminette $(SRCS)
	@echo "$(ORANGE)******************************"
	@echo "$(BLUE)        CHECK INCLUDES$(RESET)"
	@echo "$(ORANGE)******************************$(PURPLE)"
	@norminette $(INCLUDES)
	@echo "$(ORANGE)******************************$(GREEN)"
	@echo "        NO NORM ERRORS$(RESET)"
	@echo "$(ORANGE)******************************$(DEF)"

re : fclean all


#####***************************************************************************************#####
###**										Good luck!										**###
#################################################################################################