# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hermarti <hermarti@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/27 14:38:13 by hermarti          #+#    #+#              #
#    Updated: 2025/11/03 18:37:38 by hermarti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g2 -O0 -fsanitize=leak
endif

INCLUDES = -I./inc

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC_FILES = main.c \
			env.c \
			fork.c \
			philo.c \
			waiter.c \
			philo_life.c \
			check_args.c \
			error.c \
			util.c \
			util2.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "[OK] $(NAME) compiled successfully"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "[OK] Object files removed"

fclean: clean
	@rm -f $(NAME)
	@echo "[OK] $(NAME) removed"

re: fclean all

.PHONY: all clean fclean re
