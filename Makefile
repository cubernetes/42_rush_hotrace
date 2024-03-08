# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/17 17:41:15 by astavrop          #+#    #+#              #
#    Updated: 2024/03/08 22:56:28 by astavrop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					:= cc
CFLAGS				:= -Wall -Werror -Wextra -g
DEBUGFLAGS			:= -g
LIBS				:=
INCLUDES			:= -I.
NAME				:= hash_func


CFILES				+= main.c					# Main
CFILES				+= fnv_1a_hash.c


OBJ_DIR				:= ./obj/
OBJS				:= $(patsubst %.c, $(OBJ_DIR)%.o, $(CFILES))


DEPS				:= $(OBJS:.o=.d)


all: $(NAME)

.DEFAULT_GOAL := all


-include $(DEPS)


$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) $(INCLUDES) -c $< -o $@


$(NAME): $(OBJS)
	@echo -n "\033[32;49;3m... Compiling code ...\033[0m\r"
	@$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(OBJS) $(LIBS)
	@echo "\033[32;49;1m>>>   Done!   <<<\033[0m          "


test: $(NAME)
	@echo "\033[32;49;3m\tRun simple test\033[0m"
	@-./$(NAME) "key-word-1"


clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "\033[32;1mObjects cleand!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[32;1mEverything cleand!\033[0m"


re: fclean all


.PHONY: all clean fclean re