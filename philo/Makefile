# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 08:36:17 by yusengok          #+#    #+#              #
#    Updated: 2024/03/13 11:30:20 by yusengok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RESET = \033[0m
LIGHT_GREEN = \033[32m
MAGENTA = \033[95m

NAME = philo
INCLUDE = includes/

FILES = main	\
		data_check	\
		data_init	\
		data_clear	\
		th_routine	\
		th_monitor	\
		utils	\
		error_handling

HEADER_FILES = philo.h	\
				philo_print.h

vpath %c srcs
SRCS = $(addsuffix .c, $(FILES))
HEADERS = $(addprefix $(INCLUDE), $(HEADER_FILES))
OBJS_DIR = .objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
DEPS = $(OBJS:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I$(INCLUDE)

all:
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	@printf "$(MAGENTA)$(BOLD)Building philo...\n$(RESET)"
	$(CC) $(CFLAGS) $^ -o $@
	@printf "$(LIGHT_GREEN)$(BOLD)philo is ready to launch\n$(RESET)"

$(OBJS_DIR)%.o: %.c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

-include $(DEPS)

clean:
	@printf "$(MAGENTA)$(BOLD)Cleaning...\n$(RESET)"
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
