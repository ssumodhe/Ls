/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_u_r_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 20:01:42 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 22:40:21 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_run(t_args **bellow, t_flags flag)
{
	t_args	*tmp;

	if (!bellow)
		return ;
	tmp = *bellow;
	while (tmp)
	{
		create_bellow(&tmp, flag.a);
		process_flags(&tmp->bellow, flag);
		if (S_ISDIR(tmp->lstat.st_mode) != 0 && check_if_point(tmp->arg) == 0)
			ft_putendl("");
		ft_put_this_list(tmp, flag);
		if (ft_if_go_bellow(tmp) == 1)
			ft_run(&tmp->bellow, flag);
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
	while (tmp)
	{
		if (S_ISDIR(tmp->stat.st_mode) != 0 && a != 0)
			ft_putendl("");
		if (S_ISDIR(tmp->stat.st_mode) != 0)
			a++;
		ft_put_first_list(tmp, numbers, flag);
		if (tmp->bellow != NULL)
			ft_run(&tmp->bellow, flag);
		tmp = tmp->next;
	}
}
