/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_t_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:37:21 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 16:29:28 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	all_args_opt_t(t_args **args)
{
	if (!args)
		return ;
	*args = ft_mergesort(*args, ft_modif_date_mergesort);
}

void	opt_t(t_args **args)
{
	t_args	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		if (tmp->bellow != NULL)
		{
			all_args_opt_t(&tmp->bellow);
		}
		tmp = tmp->next;
	}
}
