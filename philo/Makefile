# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 08:36:17 by yusengok          #+#    #+#              #
#    Updated: 2024/05/06 11:36:04 by yusengok         ###   ########.fr        #
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
		threads	\
		th_routine	\
		th_routine_utils	\
		th_monitor_philo	\
		th_monitoir_data	\
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
#-fsanitize=thread

all:
	@$(MAKE) $(NAME)
	@printf "$(LIGHT_GREEN)$(BOLD)Ready to launch 🤔💭 $(RESET)\n"

$(NAME): $(OBJS)
	@printf "$(MAGENTA)$(BOLD)Building philo...\n$(RESET)"
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)%.o: %.c $(HEADERS) Makefile
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

-include $(DEPS)

clean:
	@printf "$(MAGENTA) Cleaning...\n$(RESET)"
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
