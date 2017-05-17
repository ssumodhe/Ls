/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_a_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:23:19 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/15 18:05:24 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.c"

void	opt_a(t_args **args)
{
	t_args	*tmp;
	char 	*split;

	tmp = (*args)->bellow;
	split = NULL;
	while (tmp)
	{
		split = ft_strwithout(tmp->arg, 2);
		ft_putendl(split);
		ft_strdel(&split);
		tmp = tmp->next;
	}
}
