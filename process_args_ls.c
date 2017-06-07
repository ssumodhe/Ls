/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args_ls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:04:06 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 22:42:05 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		all_args(t_args **args)
{
	t_args	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		if (tmp->bellow != NULL)
		{
			tmp->bellow = ft_mergesort(tmp->bellow, ft_ascii_mergesort);
		}
		tmp = tmp->next;
	}
}

void		get_stat(t_args *tmp)
{
	if ((stat(tmp->arg, &tmp->stat)) == -1)
		;
}

void		get_link_stat(t_args *tmp)
{
	if ((lstat(tmp->arg, &tmp->lstat)) == -1)
		;
}

void		create_bellow(t_args **args, int opt_a)
{
	if (!args)
		return ;
	if (opt_a == 1)
		ft_openfiles(args);
	else
		ft_openfiles_withouta(args);
	all_args(args);
}

void		process_args(t_args **args, int opt_a)
{
	t_args	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		create_bellow(&tmp, opt_a);
		tmp = tmp->next;
	}
}
