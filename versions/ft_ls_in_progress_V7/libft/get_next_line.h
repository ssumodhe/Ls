/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:25:41 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/03/09 15:36:31 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"

# define BUFF_SIZE 3000

# define RESET	   "\033[0m"
# define HIGHLIGHT "\033[1m"
# define UNDERLINE "\033[4m"
# define BLINK     "\033[5m"
# define BLACK     "\033[30m"
# define RED       "\033[31m"
# define GREEN     "\033[32m"
# define YELLOW    "\033[33m"
# define BLUE      "\033[34m"
# define PURPLE    "\033[35m"
# define CYAN      "\033[36m"
# define WHITE     "\033[37m"

typedef	struct	s_gnl
{
	int				fd;
	char			*stock;
	struct s_gnl	*next;
}				t_gnl;

t_gnl			*ft_fill_in_list(int fd);
t_gnl			*ft_fd_find_create(int fd, t_gnl **file);
int				ft_while_read(char *buff, char **line, char **stock);
int				ft_is_stock(char **stock, char **line);
int				get_next_line(const int fd, char **line);

#endif
