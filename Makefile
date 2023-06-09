# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhellad <akhellad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/09 11:58:56 by akhellad          #+#    #+#              #
#    Updated: 2023/06/09 16:09:45 by akhellad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS 	= srcs/philo.c srcs/utils.c
OBJS 	= ${SRCS:.c=.o}

HEADER	= -Iincludes

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g3 -pthread

.c.o:		%.o : %.c
					gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)
					@echo "\033[33;32m[OK] \033[0m       \033[0;33m Compiling:\033[0m" $<

all: 		${NAME}

${NAME}:	${OBJS}
					@$(CC) ${OBJS} -o ${NAME} -lpthread
					@echo "\033[0;34m[OK] \033[0m       \033[0;33m Created  \033[0m: ${NAME}" 


clean:
					@rm -f ${OBJS}
					@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${OBJS}"

fclean: 	clean
					@rm -f ${NAME}
					@echo "\033[0;31m[OK] \033[0m       \033[0;33m Deleted  \033[0m: ${NAME}"

re:			fclean all

.PHONY: all clean fclean re re_bonus bonus