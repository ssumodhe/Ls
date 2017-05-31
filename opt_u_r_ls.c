/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_u_r_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 20:01:42 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/31 13:16:35 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_put_perm_denied(t_args *file, int mode)
{
	if (mode == 1)
	{
		ft_putstr_fd(file->arg, 2);
		ft_putendl_fd(":", 2);
	}
	errno = file->error;
	ft_putstr_fd("ft_ls: ", 2);
	if (ft_strrchr(file->arg, '/') == NULL)
		perror(file->arg);
	else
		perror(ft_strrchr(file->arg, '/') + 1);

}

t_numbers	count_args_2(t_args *file)
{
	t_args		*tmp;
	t_numbers	numbers;

	tmp = file;
	numbers.n_file = 0;
	numbers.n_denied = 0;
	numbers.n_other = 0;
	numbers.removed = 0;
	while (tmp)
	{
		if (S_ISDIR(tmp->stat.st_mode) != 0)
			numbers.n_file++;
		else
			numbers.n_other++;
		tmp = tmp->next;
	}
	return (numbers);
}

void		alone_2(t_args *args)
{
	t_args	*file;
	t_numbers numbers;

	file = args;

	ft_putstr(CYAN UNDERLINE); //
	while (file) //Affiche les fichiers (file->error == 20);
	{
		//if (file->error == 20) /////// /!
		if (S_ISDIR(file->stat.st_mode) == 0) /////// /!
		{
			ft_putendl(file->arg);
		}
		file = file->next;
	}
	numbers = count_args_2(args);
	if (numbers.n_other != 0 && numbers.n_file >= 1)
		ft_putendl("ALONE_2 | ------>");
	ft_putstr(RESET); //

	/*
	file = args;
	arguments = 0;
	while (file) //Affiche les repositories et les permissions denied "de 1ier ordre"
	{
		if (file->error == 0)
		{
			arguments++;
			if ((check_if_point(file->arg) == 0))
			{
				ft_putstr(file->arg);
				ft_putendl(":");
			}
			ft_print_bellow(file);

			
		}
		else if (file->error == 13)
		{	
			arguments++;
			ft_put_perm_denied(file);
		}
		file = file->next;
	}*/
}

int			ft_if_go_bellow(t_args *tmp)
{
	if (S_ISDIR(tmp->lstat.st_mode) != 0 && (check_if_point(tmp->arg) == 0 && tmp->bellow != NULL))
		return (1);
	return (0);
}

int			check_if_point(char *str)
{
	char	*check;

	check = ft_strrchr(str, '/');
	if (check != NULL)
	{
		if (ft_strcmp(check, "/..") == 0)
			return (1);
		if (ft_strcmp(check, "/.") == 0)
			return (1);
	}
	return (0);
}

void		ft_put_this_list(t_args *args)
{
	if (S_ISDIR(args->lstat.st_mode) != 0 && check_if_point(args->arg) == 0 )
	{
		if (args->error == 13)
		{
			ft_put_perm_denied(args, 1);
		}
		else
		{
			ft_putstr(GREEN); //
			ft_putstr(args->arg);
			ft_putstr(RESET); //
			ft_putendl(":");
		}
		if (args != NULL)
			ft_print_bellow(args);
	}
}

void		ft_put_first_list(t_args *args)
{
	if (S_ISDIR(args->stat.st_mode) != 0)
	{
		if (args->error == 13)
		{
			ft_put_perm_denied(args, 1);
		}
		else
		{
			ft_putstr(GREEN); //
			ft_putstr(args->arg);
			ft_putstr(RESET); //
			ft_putendl(":");
		}
		if (args != NULL)
			ft_print_bellow(args);
	}

}


void		ft_run(t_args *bellow, t_flags flag)
{
	t_args	*tmp;

	tmp = bellow;
	while (tmp)
	{
		create_bellow(&tmp, flag.a); //creer la liste chainee
		process_flags(tmp, flag);
		ft_put_this_list(tmp);
		if (S_ISDIR(tmp->lstat.st_mode) != 0) // ici que saut en trop quand -a
			ft_putendl("FT_RUN | ------>");
		if (ft_if_go_bellow(tmp) == 1)
			ft_run(tmp->bellow, flag);
		tmp = tmp->next;
	}
}

void		opt_u_r(t_args **args, t_flags flag)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp) // attention petit l
	{
		ft_put_first_list(tmp);
		if (S_ISDIR(tmp->stat.st_mode) != 0) // ici qu'il faut intervenir si args tout seul
			ft_putendl("OPT_U_R | ------>");
		if (tmp->bellow != NULL)
		{
			ft_run(tmp->bellow, flag);
		}
		tmp = tmp->next;
	}
}
