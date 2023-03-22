# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yumaohno <yumaohno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/12 14:02:00 by yumaohno          #+#    #+#              #
#    Updated: 2023/03/12 14:10:33by yumaohno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
DEBUG_FLAG = -fsanitize=thread
SRCS =	src/main.c	\
		src/check_args/check_args.c	\
		src/init_philo/init_philo.c	\
		src/philo_thread/philo_thread.c	\
		src/philo_thread/monitor/monitor_func.c	\
		src/philo_thread/philo_func/philo_eat.c		\
		src/philo_thread/philo_func/philo_fork.c	\
		src/philo_thread/philo_func/philo_sleep.c	\
		src/philo_thread/philo_func/philo_think.c	\
		src/philo_thread/philo_func/print_message.c	\
		src/philo_thread/philo_func/get_time.c		\
		src/philo_thread/destroy/destroy_thread.c

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

INC = -I include

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -lpthread

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

debug: CFLAGS += $(DEBUG_FLAG)
debug: re

re: fclean all

.PHONY: all clean fclean re debug