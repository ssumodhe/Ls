/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_error_args_ls.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:14:20 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 15:21:51 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_free_the_removed(t_args **tmp_removed)
{
	ft_strdel(&(*tmp_removed)->arg);
	ft_strdel(&(*tmp_removed)->field);
	free((*tmp_removed));
}

int			remove_error_while(t_args *tmp, t_args **args, int removed)
{
	t_args	*free;

	free = tmp->next;
	tmp->next = tmp->next->next;
	ft_free_the_removed(&free);
	removed = remove_error_args(args, removed);
	removed++;
	return (removed);
}

int			remove_error_if(t_args *tmp, t_args **args, int removed)
{
	t_args	*free;

	free = tmp;
	tmp = tmp->next;
	ft_free_the_removed(&free);
	*args = tmp;
	removed = remove_error_args(args, removed);
	removed++;
	return (removed);

}

int			remove_error_args(t_args **args, int removed)
{
	t_args	*tmp;

	if (!args)
		return (0);
	tmp = *args;
	if (tmp != NULL && tmp->error != 0 && tmp->error != 20)
	{
		if ((tmp->error == 13 && S_ISDIR(tmp->stat.st_mode) == 0) || (tmp->error != 13))
		{
			return (remove_error_if(tmp, args, removed));
		}
	}
	while (tmp)
	{
		if (tmp->next != NULL && tmp->next->error != 0 && tmp->next->error != 20)
		{
			if ((tmp->next->error == 13 && S_ISDIR(tmp->next->stat.st_mode) == 0) || (tmp->next->error != 13))
			{
				return (remove_error_while(tmp, args, removed));
			}
		}
		tmp = tmp->next;
	}
	return (removed);
}

