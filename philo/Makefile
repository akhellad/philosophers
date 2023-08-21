# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 10:57:00 by akhellad          #+#    #+#              #
#    Updated: 2023/08/21 11:26:38 by akhellad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = philo

SRCS_DIR = srcs/
OBJS_DIR = objs/
INC_DIR = includes/

SRCS    = main.c \
		ft_atoi.c \
		philo.c \
		threads.c \
		time.c \
		utils.c

OBJS    = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))

HEADER  = -Iincludes
INC     = ${INC_DIR}*.h

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g3 -pthread


all:        ${NAME}

${NAME}:    ${OBJS}
			@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m: ${NAME}"
			@$(CC) ${OBJS} -lpthread -o ${NAME}

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c Makefile ${INC}
			@mkdir -p $(OBJS_DIR)
			@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<
			@$(CC) ${CFLAGS} ${HEADER} -c $< -o $@

check:
			norminette ${SRCS_DIR} ${INC_DIR}

clean:
			@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${OBJS}"
			@rm -f ${OBJS}
			@rm -rf ${TMP_DIR}

fclean:    	clean
			@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${NAME}"
			@rm -f ${NAME}
			@rm -rf $(OBJS_DIR)

re:         fclean all

.PHONY: all clean fclean re force