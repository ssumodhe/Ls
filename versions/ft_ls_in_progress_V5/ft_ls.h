/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:59 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/27 22:22:31 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h> //opendir etc
# include <sys/errno.h> //errno's define
# include <time.h> //ctime function

typedef	struct		s_numbers
{
	int		n_file;
	int		n_denied;
	int		n_other;
	int		removed;
}					t_numbers;

typedef struct		s_flags
{
	int		l;
	int		u_r;
	int		a;
	int		l_r;
	int		t;
	int		none;
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
	struct stat			stat;
	struct s_args		*bellow;
	struct s_args		*next;
	struct s_args		*prev;
}					t_args;

/*
** get_lists.c
*/
t_option			*fill_option(int i, char *opt, t_option *option);
t_args				*fill_args(int i, char *arg, t_args *argmt);
t_args				*new_args(int i, char *arg);

/*
** prog_ls.c
*/
void				ft_prog(t_option *opt, t_args *args);
t_numbers			count_args(t_args **args);
int					remove_error_args(t_args **args, int removed);
void				put_error_args(t_args **args);
void				get_error_args(t_args **args);
t_flags				check_opt(t_option *opt, t_flags flag);
t_flags				fill_flag(t_flags flag, char c);
t_flags				init_flag(void);

/*
** mergesort_ls.c
*/
t_args				*ft_mergesort(t_args *merge, void f());
t_args				*ft_glue_mergesort(t_args *left, t_args *right, void f());
int					ft_lstcount(t_args **merge);
void				ft_descendingorder_mergesort(t_args **tmp, t_args **left, t_args **right);
void				ft_ascii_mergesort(t_args **tmp, t_args **left, t_args **right);
void				ft_modif_date_mergesort(t_args **tmp, t_args **left, t_args **right);

/*
** process_args_ls.c
*/
//void				process_args(t_args **args);
void				process_args(t_args **args, int opt_a);
void				ft_openfiles(t_args **args);
char				*ft_strjoin_by(char *str1, char c, char *str2);
void				put_args(t_args **args);
void				all_args(t_args **args);

/*
** process_args_ls.c
*/
void				process_flags(t_args *args, t_flags flag, t_numbers numbers);

/*
** alone_ls.c
*/
void				alone(t_args **args, t_numbers numbers);
void				ft_print_bellow(t_args *file);
char				*ft_strwithoutstrat(char *str, int size);

/*
** opt_t_ls.c
*/
void				opt_t(t_args **args);
void				all_args_opt_t(t_args **args);

/*
** opt_r_ls.c
*/
void				opt_r(t_args **args);
void				all_args_opt_r(t_args **args);

#endif
