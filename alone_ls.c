/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:00:04 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 02:41:16 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_bellow(t_args *file, t_flags flag)
{
	t_args	*tmp;
	char	*split;

	split = NULL;
	tmp = file->bellow;
	if (tmp && flag.l == 1)
	{
		ft_putstr("total ");
		ft_putnbr(tmp->l_total);
		ft_putendl("");
	}
	while (tmp)
	{
		if (flag.l == 1)
			ft_putendl(tmp->field);
		else
		{
			split = (ft_strrchr(tmp->arg, '/') + 1);
			if (split != NULL)
				ft_putendl(split);
			else
				ft_putendl(tmp->arg);
		}
		tmp = tmp->next;
	}
}

void	alone(t_args **args, t_flags flag, t_numbers numbers)
{
	t_args	*tmp;
	int		arguments;

	if (!args)
		return ;
	arguments = 1;
	alone_2(*args, flag);
	tmp = *args;
	while (tmp)
	{
		ft_put_first_list(tmp, numbers, flag);
		if (S_ISDIR(tmp->stat.st_mode) != 0 && arguments < numbers.n_file)
		{
			arguments++;
			ft_putendl("");
		}
		tmp = tmp->next;
	}
}
