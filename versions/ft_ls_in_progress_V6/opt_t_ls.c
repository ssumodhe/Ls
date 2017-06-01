/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_t_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:37:21 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/31 18:38:41 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	all_args_opt_t(t_args **args)
{
	*args = ft_mergesort(*args, ft_modif_date_mergesort);
}

void	opt_t(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		if (tmp->bellow != NULL)
		{
			all_args_opt_t(&tmp->bellow);
			opt_t(&tmp->bellow);
		}
		tmp = tmp->next;
	}
}
