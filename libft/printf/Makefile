# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 16:32:06 by clouden           #+#    #+#              #
#    Updated: 2025/07/01 20:21:36 by clouden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Complier and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I./include
CFLAGS += -g3
# Name of the output static library
NAME	= libftprintf.a

# Source and object files
SRCS	= ft_printf.c\
			ft_printf_utils.c
OBJS	= $(SRCS:.c=.o)

# Test file
TEST_SRC = .test.c
TEST_OBJ = $(TEST_SRC:.c=.o)
TEST_BIN = test_printf

# Default rule
all: $(NAME)

# Rule to build the library from object files
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Rule to compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Optional build test
test: $(TEST_OBJ) $(NAME)
	$(CC) $(CFLAGS) $^ -o $(TEST_BIN)

# Clean object files
clean:
	rm -f $(OBJS) $(TEST_OBJ)

# Clean object files
fclean: clean
	rm -f $(NAME) $(TEST_BIN)

# Rebuild
re: fclean all

.PHONY: all test clean fclean re
