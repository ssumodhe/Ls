/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:59 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 17:53:28 by ssumodhe         ###   ########.fr       */
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

# define PB_CLOSE_DIR "We seem to reach a probleme when closing the directory"

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
void				ft_get_lists(int argc, char **argv, t_option **opt, t_args **args);
t_option			*fill_option(int i, char *opt, t_option *option);
t_args				*fill_args(int i, char *arg, t_args *argmt);
t_args				*new_args(int i, char *arg);

/*
** prog_ls.c
*/
void				ft_prog(t_option *opt, t_args **args);
void				ft_if_upper_r(t_args **args, t_flags flag, t_numbers numbers);
void				ft_if_no_ur(t_args **args, t_flags flag, t_numbers numbers);
void				put_error_args(t_args **args);
void				get_error_args(t_args **args);

/*
** flags_opt_number_ls.c
*/
t_flags				check_opt(t_option *opt, t_flags flag);
t_flags				fill_flag(t_flags flag, char c);
t_flags				init_flag(void);
t_numbers			get_numbers(t_args *args, t_flags flag);

/*
** remove_error_args_ls.c
*/
int					remove_error_args(t_args **args, int removed);
int					remove_error_if(t_args *tmp, t_args **args, int removed);
int					remove_error_while(t_args *tmp, t_args **args, int removed);
void				ft_free_the_removed(t_args **tmp_removed);

/*
** mergesort_ls.c
*/
t_args				*ft_mergesort(t_args *merge, void f());
t_args				*ft_glue_mergesort(t_args *left, t_args *right, void f());
void				ft_put_side(t_args **tmp, t_args **side);
int					ft_lstcount(t_args **merge);

/*
** mergesort_mod_ls.c
*/
void				ft_ascii_mergesort(t_args **tmp, t_args **left, t_args **right);
void				ft_modif_date_mergesort(t_args **tmp, t_args **left, t_args **right);

/*
** process_args_ls.c
*/
void				process_args(t_args **args, int opt_a);
void				create_bellow(t_args **args, int opt_a);
void				get_link_stat(t_args *tmp);
void				get_stat(t_args	*tmp);
void				all_args(t_args **args);

/*
** openfiles_ls.c
*/
void				ft_openfiles(t_args **args);
void				ft_openfiles_withouta(t_args **args);
void				ft_put_bellow_file(t_args **args, struct dirent *d);
t_args				*args_newlist(char *str, struct dirent *d);
char				*ft_strjoin_by(char *str1, char c, char *str2);

/*
** process_flags_ls.c
*/
void				process_flags(t_args **args, t_flags flag);

/*
** alone_ls.c
*/
void				alone(t_args **args, t_flags flag, t_numbers numbers);
void				ft_print_bellow(t_args *file, t_flags flag);
void				alone_2(t_args *args, t_flags flag);
t_numbers			count_args_2(t_args *file);
void				ft_put_perm_denied(t_args *file);

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
void				ft_reverse(t_args **args, t_args *tmp, t_args *before);

/*
** opt_u_r_ls.c
*/
void				opt_u_r(t_args **args, t_flags flag, t_numbers numbers);
void				ft_run(t_args **args, t_flags flag);

/*
** put_lists_ls.c
*/
void				ft_put_first_list(t_args *args, t_numbers numbers, t_flags flag);
void				ft_put_this_list(t_args *args, t_flags flag);
int					check_if_point(char *str);
int					ft_if_go_bellow(t_args *tmp);

/*
** opt_l_r_ls.c
*/
void				opt_l(t_args **args);
int					all_args_opt_l(t_args *args);
t_max				ft_cmp_max(t_args *tmp, t_max max);
t_max				ft_init_max(void);

/*
** creat_field_ls.c
*/
void				ft_get_info_item(t_args *tmp);
char				ft_get_filetype(t_args *tmp);
char				*ft_create_field(int n, t_args *tmp, t_max max); //+1

/*
** creat_field_2_ls.c
*/
void				ft_size_maj_min(char *field, t_args *tmp, int start, int end); //+1
void				ft_put_size(char *field, t_args *tmp, int start, int end);
void				ft_put_time(char *field, t_args *tmp);

/*
** creat_field_3_ls.c
*/
void				ft_put_perm(char *field, t_args *tmp);
void				ft_put_ext_perm(char *field, t_args *tmp, int usr, int grp, int oth);
void				ft_put_hardlink(char *field, t_args *tmp, int i);
void				ft_put_usr(char *field, char *usr, int end);
void				ft_put_grp(char *field, char *grp, int end);

#endif
