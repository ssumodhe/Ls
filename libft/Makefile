# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/08 11:04:13 by ssumodhe          #+#    #+#              #
#    Updated: 2017/04/04 16:15:23 by ssumodhe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Werror -Wextra

NAME = libft.a

INCLUDES = libft.h get_next_line.h

SRCS = get_next_line.c \
	   ft_intlen.c ft_isspace.c ft_atoi_base.c ft_exit.c\
	   ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
	   ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
	   ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
	   ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
	   ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	   ft_isprint.c ft_toupper.c ft_tolower.c \
	   ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	   ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
	   ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
	   ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	   ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	   ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c \
	   ft_lstmap.c

OBJECT = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJECT)
	@gcc $(FLAGS) -c $(SRCS)
	@ar rc $(NAME) $(OBJECT)
	@echo "Libft: \033[1;32mDONE\033[0m"

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJECT)
	@echo "Libft: clean: \033[1;32mDONE\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "Libft: fclean: \033[1;32mDONE\033[0m"

re: fclean all
