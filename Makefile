# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clouden <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/17 14:56:26 by clouden           #+#    #+#              #
#    Updated: 2025/10/28 19:25:28 by clouden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


RED		=	\033[0;31m
GREEN   =	\033[0;32m
RESET   =	\033[0m  
YELLOW  =	\033[1;33m
BLUE    =	\033[0;34m

MAKE	= make

CC		=	cc
CFLAGS	=	-lreadline -g3 -Iincludes -Ilibft/include -fsanitize=address  #-Wall -Wextra -Werror

NAME	=	minishell

SRCS	=	init.c \
			clean.c \
			env_ops.c \
			automata.c \
			token_utils.c \
			utils.c \
			executor.c \
			builtins.c \
			builtin_utils.c

OBJS	=	$(SRCS:%.c=%.o)

MAIN	= 	main.c
MAIN_OBJ=	$(MAIN:.c=.o)

LIBFT_DIR 	=	libft/
LIBFT		=	$(LIBFT_DIR)libft.a

all:$(NAME)

$(NAME):$(OBJS) $(MAIN_OBJ) $(LIBFT)
	@echo "$(BLUE)[$(NAME)]$(RESET) $^ → $@"
	@$(CC) $(CFLAGS) $^ -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all --no-print-directory

%.o: %.c
	@printf "$(BLUE)[COMPILING]$(RESET) %-21s → %s\n" $< $@
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_NAME)

clean:
	@echo "$(YELLOW)"
	@echo "+---------------------------+"
	@echo "|  🧹  CLEANING OBJECTS     |"
	@echo "+---------------------------+"
	@rm -rf *.o $(OBJS) $(MAIN_OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@echo "$(RED)"
	@echo "+---------------------------+"
	@echo "|  🔥 REMOVING EXECUTABLES  |"
	@echo "+---------------------------+"
	@rm -f $(NAME)  
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RESET)"
	@echo "...now THAT'S effin' clean!\n"

re: fclean all

.PHONY: re all clean fclean

