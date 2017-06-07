/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:59 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 03:06:28 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h> //opendir etc
# include <sys/errno.h> //errno's define
# include <time.h> //ctime function
# include <sys/types.h> //getpwuid function
# include <pwd.h> //getpwuid function
# include <grp.h> //getgrgid function
# include <uuid/uuid.h> //getpwuid & getgrgid function

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

typedef struct			s_info
{
	int		hard_link;
	char	*usr;
	char	*grp;
	int		size;
	char	*link;
	int		maj;
	int		min;
}						t_info;


typedef struct		s_args
{
	int					i;
	char				*arg;
	char				*field;
	int					error;
	struct stat			lstat;
	struct stat			stat;
	struct passwd		*pwuid;
	struct group		*grgid;
	struct s_info		info;
	int					l_total;
	struct s_args		*bellow;
	struct s_args		*next;
	struct s_args		*prev;
}					t_args;

typedef struct			s_max
{
	int		hard_link;
	int		usr;
	int		grp;
	int		size;
}						t_max;

/*
** get_lists.c
*/
//void				ft_get_lists(int argc, char **argv, t_option **opt, t_args **args);
t_option			*fill_option(int i, char *opt, t_option *option);
t_args				*fill_args(int i, char *arg, t_args *argmt);
t_args				*new_args(int i, char *arg);

/*
** prog_ls.c
*/
void				ft_prog(t_option *opt, t_args **args);
void				ft_if_upper_r(t_args **args, t_flags flag, t_numbers numbers);
void				ft_if_no_ur(t_args **args, t_flags flag, t_numbers numbers);
t_numbers			get_numbers(t_args *args, t_flags flag);
//t_numbers			count_args(t_args **args);
int					remove_error_args(t_args **args, int removed);
void				ft_free_the_removed(t_args **tmp_removed);
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
//void				ft_descendingorder_mergesort(t_args **tmp, t_args **left, t_args **right);
void				ft_ascii_mergesort(t_args **tmp, t_args **left, t_args **right);
void				ft_modif_date_mergesort(t_args **tmp, t_args **left, t_args **right);

/*
** process_args_ls.c
*/
void				process_args(t_args **args, int opt_a);
void				create_bellow(t_args **args, int opt_a);
void				ft_openfiles(t_args **args);
void				ft_openfiles_withouta(t_args **args);
t_args				*args_newlist(char *str, struct dirent *d);
void				get_link_stat(t_args *tmp);
void				get_stat(t_args	*tmp);
char				*ft_strjoin_by(char *str1, char c, char *str2);
void				all_args(t_args **args);

/*
** process_flags_ls.c
*/
void				process_flags(t_args **args, t_flags flag);

/*
** alone_ls.c
*/
void				alone(t_args **args, t_flags flag, t_numbers numbers);
void				ft_print_bellow(t_args *file, t_flags flag);

/*
** opt_t_ls.c
*/
void				opt_t(t_args **args);
void				all_args_opt_t(t_args **args);

/*
** opt_l_r_ls.c
*/
void				opt_l_r(t_args **args);
void				all_args_opt_r(t_args **args);

/*
** opt_u_r_ls.c
*/
void				opt_u_r(t_args **args, t_flags flag, t_numbers numbers);
void				ft_run(t_args **args, t_flags flag);
void				ft_put_first_list(t_args *args, t_numbers numbers, t_flags flag);
void				ft_put_this_list(t_args *args, t_flags flag);
int					check_if_point(char *str);
void				ft_put_perm_denied(t_args *file);
void				alone_2(t_args *args, t_flags flag);

/*
** opt_l_r_ls.c
*/
void				opt_l(t_args **args);
int					all_args_opt_l(t_args *args);
void				ft_get_info_item(t_args *tmp);
t_max				ft_cmp_max(t_args *tmp, t_max max);
t_max				ft_init_max(void);

#endif
