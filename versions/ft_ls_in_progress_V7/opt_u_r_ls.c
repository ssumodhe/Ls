/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_u_r_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 20:01:42 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/06 20:36:34 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_put_perm_denied(t_args *file)
{
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


void		alone_2(t_args *args, t_flags flag)
{
	t_args	*file;
	t_numbers numbers;

	file = args;

	while (file) //Affiche les fichiers (file->error == 20);
	{
		if (flag.l == 1 && S_ISDIR(file->lstat.st_mode) == 0) // ATTENTION PETIT L
		{
			ft_putendl(file->field);
		}
		else if (flag.l == 0 && S_ISDIR(file->stat.st_mode) == 0)
		{
			ft_putendl(file->arg); // + l
		}
		file = file->next;
	}
	numbers = count_args_2(args);
	if (numbers.n_other != 0 && numbers.n_file >= 1)
		ft_putendl("");
}

int			ft_if_go_bellow(t_args *tmp)
{
//	ft_putstr(tmp->arg);
//		ft_putendl(YELLOW HIGHLIGHT ITALIC"  Je passe ici"RESET);
	if (!tmp)
		return (0);
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

void		ft_put_this_list(t_args *args, t_flags flag)
{
//	if (!args)
//		return ;
	if (args && S_ISDIR(args->lstat.st_mode) != 0 && check_if_point(args->arg) == 0)
	{	
		ft_putstr(RED); //
		ft_putstr(args->arg);
		ft_putstr(RESET); //
		ft_putendl(":");

		if (args->error == 13)
		{
			ft_put_perm_denied(args);
		}
		else if (args != NULL)
		{
			// INTEGRER TOTAL PETIT L // au final mis dans print_bellow
			ft_print_bellow(args, flag);
		}
	}
}

void		ft_put_first_list(t_args *args, t_numbers numbers, t_flags flag)
{
/*	ft_putendl("Je suis au debut first list");
	ft_putstr("nom = ");
	ft_putstr(args->arg);
	ft_putendl("");
	ft_putstr("stat mode = ");
	ft_putnbr(S_ISDIR(args->stat.st_mode));
	ft_putendl("");
	ft_putstr("lstat mode = ");
	ft_putnbr(S_ISDIR(args->lstat.st_mode));
	ft_putendl("");*/

	if (!args)
		return ;
	if ((flag.l == 0 && S_ISDIR(args->stat.st_mode) != 0) || (flag.l == 1 && S_ISDIR(args->lstat.st_mode) != 0))
	{
		if (numbers.n_file > 1 || numbers.removed >= 1 || numbers.n_other >= 1) //
		{
			ft_putstr(GREEN); //
			ft_putstr(args->arg);
			ft_putstr(RESET); //
			ft_putendl(":");
		}
		if (args->error == 13) //ajouter une condition pour gerer munki => version SARAH
		{
			ft_put_perm_denied(args);
		}
		else if (args != NULL)
		{
			// INTEGRER TOTAL PETIT L // au final mis dans print_bellow
			ft_print_bellow(args, flag);
		}
	}
}


void		ft_run(t_args **bellow, t_flags flag)
{
	t_args	*tmp;

	if (!bellow)
		return ;
	tmp = *bellow;
	while (tmp)
	{
		create_bellow(&tmp, flag.a); //creer la liste chainee
		process_flags(&tmp->bellow, flag);
		if (S_ISDIR(tmp->lstat.st_mode) != 0 && check_if_point(tmp->arg) == 0) // ici que saut en trop quand -a
			ft_putendl("");
		ft_put_this_list(tmp, flag);
		if (ft_if_go_bellow(tmp) == 1)
		{
			ft_run(&tmp->bellow, flag);
//			ft_putendl(YELLOW HIGHLIGHT ITALIC"Je passe ici"RESET);
		}
		tmp = tmp->next;
	}
}

void		opt_u_r(t_args **args, t_flags flag, t_numbers numbers)
{
	t_args	*tmp;
	int		a;

	if (!args)
		return ;
	tmp = *args;
	a = 0;
	while (tmp) // attention petit l (courrrrrrrrs)
	{
		if (S_ISDIR(tmp->stat.st_mode) != 0 && a != 0) // ici qu'il faut intervenir si args tout seul
			ft_putendl("");
		if (S_ISDIR(tmp->stat.st_mode) != 0) 
			a++;
		ft_put_first_list(tmp, numbers, flag);
//		if (S_ISDIR(tmp->stat.st_mode) != 0) // ici qu'il faut intervenir si args tout seul
//			ft_putendl("OPT_U_R | ------>");
		if (tmp->bellow != NULL)
		{
			ft_run(&tmp->bellow, flag);
		}
		tmp = tmp->next;
	}
}
