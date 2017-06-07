/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l_r_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 20:35:14 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 02:42:05 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_reverse(t_args **args, t_args *tmp, t_args *before)
{
	t_args	*tmp_2;

	tmp_2 = tmp;
	before = tmp_2;
	while (tmp->prev != NULL)
	{
		tmp_2->next = tmp->prev;
		tmp_2 = tmp_2->next;
		tmp = tmp->prev;
	}
	tmp_2->next = NULL;
	tmp = *args;
	*args = before;
}

void	all_args_opt_r(t_args **args)
{
	t_args	*tmp;
	t_args	*before;

	if (!args)
		return ;
	tmp = *args;
	before = NULL;
	while (tmp->next != NULL)
	{
		tmp->prev = before;
		before = tmp;
		tmp = tmp->next;
	}
	tmp->prev = before;
	ft_reverse(args, tmp, before);
}

void	opt_l_r(t_args **args)
{
	t_args	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		if (tmp->bellow != NULL)
		{
			all_args_opt_r(&tmp->bellow);
		}
		tmp = tmp->next;
	}
}
