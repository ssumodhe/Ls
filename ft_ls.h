/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:59 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/05 11:41:14 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h> //opendir etc
# include <sys/errno.h> //errno's define

typedef struct		s_flags
{
	int		l;
	int		u_r;
	int		a;
	int		l_r;
	int		t;
}					t_flags;

typedef struct		s_option
{
	int					i;
	char				*opt;
	struct s_option		*next;
}					t_option;

typedef struct		s_args
{
	int					i;
	char				*arg;
	int					error;
	struct dirent		*d;
	struct s_args		*bellow;
	struct s_args		*next;
}					t_args;

/*
** get_lists.c
*/
t_option			*fill_option(int i, char *opt, t_option *option);
t_args				*fill_args(int i, char *arg, t_args *argmt);

/*
** prog_ls.c
*/
void				ft_prog(t_option *opt, t_args *args);

/*
** process_args_ls.c
*/
void				process_args(t_args **args);

/*
** alone_ls.c
*/
void				alone(t_args **args);
#endif
