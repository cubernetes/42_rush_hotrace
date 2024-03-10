# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/17 17:41:15 by astavrop          #+#    #+#              #
#    Updated: 2024/03/10 23:24:36 by astavrop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					:= cc
CFLAGS				:= -Wall -Werror -Wextra -pedantic -O3
LIBS				:=
INCLUDES			:= -I. -Iinclude/
NAME				:= hotrace

ifeq ($(DEBUG), 1)
	CFLAGS += -g3 -O0
endif

CFILES				+= main.c					# Main
CFILES				+= hash_funcs/fnv_hash.c	# Fowler–Noll–Vo hash function
CFILES				+= hash_funcs/fasthash.c	#
CFILES				+= hash_funcs/elfhash.c		# normal & gnu implementation
CFILES				+= ht.c						# Hash table
CFILES				+= utils.c					# ft_*
CFILES				+= utils2.c					# ft_*
CFILES				+= gnl/gnl.c					#
CFILES				+= gnl/gnl_utils.c				#

OBJ_DIR				:= ./obj/
OBJS				:= $(patsubst %.c, $(OBJ_DIR)%.o, $(CFILES))

DEPS				:= $(OBJS:.o=.d)

RM					:= /bin/rm -f
MKDIR				:= /bin/mkdir -p

all: $(NAME)

.DEFAULT_GOAL := all

-include $(DEPS)

$(OBJ_DIR)%.o: */%.c
	@$(MKDIR) $(@D)
	@$(CC) $(CFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@echo -n "\033[32;49;3m... Compiling code ...\033[0m\r"
	@$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(OBJS) $(LIBS)
	@echo "\033[32;49;1m>>>   Done!   <<<\033[0m          "

test: $(NAME)
	@echo "\033[32;49;3m\tRun simple test\033[m"
	@-./$(NAME) "key-word-1"

clean:
	@$(RM) $(OBJS)
	@$(RM) -r $(OBJ_DIR)
	@echo "\033[32;1mObjects cleand!\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[32;1mEverything cleand!\033[0m"

re: fclean all

.PHONY: all clean fclean re test
