# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/30 20:36:48 by ssumodhe          #+#    #+#              #
#    Updated: 2017/05/02 17:13:41 by ssumodhe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Werror -Wextra
EXEC = ft_ls
LIBFT = libft/libft.a
SRCS = main_ls.c \
	   get_lists_ls.c \
	   prog_ls.c \
	   process_args_ls.c \
	   alone_ls.c \

OBJS = $(SRCS:.c=.o)


all : $(EXEC)

$(EXEC) : $(OBJS) $(LIBFT)
	@clang $(FLAGS) -o $@ $(LIBFT) $(SRCS)
	@echo "Ft_ls: \033[1;32mDONE\033[0m"

$(LIBFT) :
	@make -C libft

%.o: %.c
	@clang $(FLAGS) -o $@ -c $<

clean :
	@make -C libft clean
	@rm -rf *.o
	@echo "Ft_ls: clean: \033[1;32mDONE\033[0m"

fclean : clean
	@make -C libft fclean
	@rm -rf $(EXEC)
	@echo "Ft_ls: fclean: \033[1;32mDONE\033[0m"

re : fclean all
