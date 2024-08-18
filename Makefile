# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gdel-val <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:37:27 by gdel-val          #+#    #+#              #
#    Updated: 2024/04/23 16:37:36 by gdel-val         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = src
SRC_BONUS_DIR = src_bonus

OBJ_DIR = objs

SRC =	pipex_utils.c	\
		main.c			\
		checker.c		\

SRC_BONUS =	main_bonus.c		\
			pipex_utils_bonus.c \
			checker_bonus.c		\
			checker.c			\
			pipex_utils.c		\

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS:.c=.o))

CC = gcc
FLAGS = -Wall -Wextra -Werror
INCLUDE = -I includes
DEBUG = -g -fsanitize=address
RM = rm -rf

LIBFT_DIR = libft/
LIBFT_A = libft.a
LIBFT = -L$(LIBFT_DIR) -lft

RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) --silent
	@echo "$(GREEN)Compiling the PIPEX program.$(CLEAR)"
	$(CC) $(FLAGS) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	@echo "$(BLUE)Removing compiled files.$(CLEAR)"
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --silent
	@echo "$(BLUE)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@echo "$(BLUE)Removing exec. files.$(CLEAR)"
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean --silent
	@echo "$(BLUE)Object files and binary removed correctly\n$(CLEAR)"

debug: $(OBJS)
	@make -C $(LIBFT_DIR) --silent
	@echo "$(PINK)Compiling for debugging the PIPEX program.$(CLEAR)"
	$(CC) $(DEBUG) $(INCLUDE) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(PINK)[OK]\n$(CLEAR)$(PINK)Success!$(CLEAR)\n"

bonus: $(OBJS_BONUS)
	@make -C $(LIBFT_DIR) --silent
	@echo "$(PINK)Compiling the PIPEX BONUS program.$(CLEAR)"
	$(CC) $(FLAGS) $(INCLUDE) $(OBJS_BONUS) $(LIBFT) -o $(NAME)
	@echo "$(PINK)[OK]\n$(CLEAR)$(PINK)Success!$(CLEAR)\n"

debug_bonus: $(OBJS_BONUS)
	@make -C $(LIBFT_DIR) --silent
	@echo "$(PINK)Compiling for debugging the PIPEX BONUS program.$(CLEAR)"
	$(CC) $(DEBUG) $(INCLUDE) $(OBJS_BONUS) $(LIBFT) -o $(NAME)
	@echo "$(PINK)[OK]\n$(CLEAR)$(PINK)Success!$(CLEAR)\n"

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean debug bonus re re_bonus
