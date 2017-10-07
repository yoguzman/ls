#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yguzman <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/07/18 11:38:09 by yguzman           #+#    #+#              #
#    Updated: 2017/02/02 16:45:34 by yguzman          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			=		clang

NAME		=		ft_ls

DIR_SRC		=		./src/

SRCS		=		$(DIR_SRC)main.c					\
					$(DIR_SRC)pars.c					\
					$(DIR_SRC)disp.c					\
					$(DIR_SRC)tools.c					\
					$(DIR_SRC)le_grand_r.c				\
					$(DIR_SRC)fill_struct.c				\
					$(DIR_SRC)info_l.c					\
					$(DIR_SRC)free.c					\
					$(DIR_SRC)sort2_1.c					\
					$(DIR_SRC)sort2_0.c					\
					$(DIR_SRC)sort.c					\
					$(DIR_SRC)sort2.c					\
					$(DIR_SRC)putstr_ls.c				\
					$(DIR_SRC)fill_flag.c

OBJS		=		$(SRCS:.c=.o)

CFLAGS		+=		-Iinclude
CFLAGS		+=		-Wall -Wextra -g -g3

RM			=		rm -f

LIB			=		./libft/libft.a

ECHO		=		printf

all			:		$(NAME)

$(NAME)		:		$(OBJS)
					@make -C libft
					@$(ECHO) "\033[35m[~~~~COMPILATION PROJECT~~~~]\n\033[0m"
					@$(CC) -o $(NAME) -Llibft -lft $(OBJS) && $(ECHO) "\033[33;32m["$@"]\n\033[0m" || $(ECHO) "\033[31m["$@"]\n\033[0m"

%.o			:		%.c
					@$(ECHO) "\033[35m[~~~Comipilation obj //project~~~]-->\033[0m"
					@$(CC) $(CFLAGS) -o $@ -c $< && $(ECHO) "\033[33;32m ["$@"]\n\033[0m" || $(ECHO) "\033[31m ["$@"]\n\033[0m"

clean_lib	:
					@make -C libft clean

clean		:		clean_lib
					@$(ECHO) "\033[31m[~~~~~~Supression des .o //project~~~~~~]\n\033[0m"
					@$(RM) $(OBJS)

fclean_lib	:
					@make -C libft fclean

fclean		:		fclean_lib
					@$(ECHO) "\033[31m[~~~~~~Supression des .o //project~~~~~~]\n\033[0m"
					@$(RM) $(OBJS)
					@$(ECHO) "\033[31m[~~~~Supression du Binaire~~~~]\n\033[0m"
					@$(RM) $(NAME)

re			:		fclean all

depend		:		$(SRCS)
					makedepend -- -Yinclude/ -- $^

.PHONY		:		all depend clean flean re

# DO NOT DELETE THIS LINE -- make depend depends on it.

src/main.o: include/libft.h include/ls.h
src/pars.o: include/ls.h include/libft.h
src/disp.o: include/ls.h include/libft.h
src/tools.o: include/libft.h
src/le_grand_r.o: include/ls.h include/libft.h
src/fill_struct.o: include/libft.h include/ls.h
src/info_l.o: include/libft.h include/ls.h
src/sort2_0.o: include/libft.h include/ls.h
src/sort.o: include/ls.h include/libft.h
src/sort2.o: include/ls.h include/libft.h
src/fill_flag.o: include/libft.h
