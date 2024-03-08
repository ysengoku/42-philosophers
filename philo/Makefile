# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 08:36:17 by yusengok          #+#    #+#              #
#    Updated: 2024/03/08 08:55:46 by yusengok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BOLD = \033[1m
RESET = \033[0m
LIGHT_GREEN = \033[32m
MAGENTA = \033[95m

NAME = philo
HEADER = philo.h

FILES = main	\
		utils

vpath %c srcs
SRCS = $(addsuffix .c, $(FILES))
OBJS_DIR = .objs/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

CC = cc
CFLAGS = -Wall -Wextra -Werror -I .
INCLUDE = -I .
RM = rm -f

all:
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	@printf "$(MAGENTA)$(BOLD)Building philo...\n$(RESET)"
	$(CC) $(CFLAGS) $^ -o $@
	@printf "$(LIGHT_GREEN)$(BOLD)philo is ready to launch\n$(RESET)"

$(OBJS_DIR)%.o: %.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

clean:
	@printf "$(MAGENTA)$(BOLD)Cleaning...\n$(RESET)"
	@$(RM) -r $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY all clean fclean re
