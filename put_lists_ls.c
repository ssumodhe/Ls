/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lists_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:50:39 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 16:59:30 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_if_go_bellow(t_args *tmp)
{
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
	if (!args)
		return ;
	if (S_ISDIR(args->lstat.st_mode) != 0 && check_if_point(args->arg) == 0)
	{	
		ft_putstr(args->arg);
		ft_putendl(":");
		if (args->error == 13)
			ft_put_perm_denied(args);
		else if (args != NULL)
			ft_print_bellow(args, flag);
	}
}

void		ft_put_first_list(t_args *args, t_numbers numbers, t_flags flag)
{
	if (!args)
		return ;
	if ((flag.l == 0 && S_ISDIR(args->stat.st_mode) != 0) || (flag.l == 1 && S_ISDIR(args->lstat.st_mode) != 0))
	{
		if (numbers.n_file > 1 || numbers.removed >= 1 || numbers.n_other >= 1)
		{
			ft_putstr(args->arg);
			ft_putendl(":");
		}
		if (args->error == 13)
			ft_put_perm_denied(args);
		else if (args != NULL)
			ft_print_bellow(args, flag);
	}
}

