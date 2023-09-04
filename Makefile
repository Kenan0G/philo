# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgezgin <kgezgin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 14:33:56 by kgezgin           #+#    #+#              #
#    Updated: 2023/09/05 00:41:38 by kgezgin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_DIR = objs
SRCS_DIR = $(shell find srcs -type d)

vpath %.c $(foreach dir, $(SRCS_DIR), $(dir))
SRCS =	main.c\
		check_args.c\
		cleaning.c\
		death.c\
		eat_sleep.c\
		routine.c\
		utils_2.c\
		utils.c

OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

DEPS = $(OBJS:%.o=%.d)

NAME = philosophers
NORM = norminette

########################### COMPILATION AND FLAGS ###########################

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address

##################################### COLOR ##################################

COLOUR_PURPLE = \033[0;35m
COLOUR_END = \033[0m

##################################### MAIN ###################################

all: $(NAME)

##################################### MANDATORY ##############################

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) includes/philo.h
	@echo "\n\t$(COLOUR_PURPLE)***EXECUTABLE CREATED SUCCESSFULL***\n\n$(COLOUR_END)"

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -lpthread -o $@ -c $<

$(OBJS_DIR):
	mkdir -p $@
	@echo "\n\t$(COLOUR_PURPLE)OBJECT DIRECTORY CREATED\n\n$(COLOUR_END)"

clean:
	rm -rf $(OBJS) $(OBJS_DIR) $(DEPS)
	@echo "\n\t$(COLOUR_PURPLE)OBJECT DIRECTORY CREATED\n\n$(COLOUR_END)"

fclean: clean
	rm -rf $(NAME)
	@echo "\n\t$(COLOUR_PURPLE)DELETE EXECUTABLE SUCCESSFULL\n\n$(COLOUR_END)"

norm:
	@echo "$(COLOUR_PURPLE)***CHECK NORM FILES***$(COLOUR_END)"
	@$(NORM)

re: fclean
	make all

.PHONY: all clean fclean norm re

-include $(DEPS)