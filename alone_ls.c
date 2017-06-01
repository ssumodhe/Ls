/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:00:04 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/01 19:48:58 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_print_bellow(t_args *file, t_flags flag)
{
	t_args	*tmp;
	char 	*split;

	split = NULL;
	tmp = file->bellow;
	while (tmp)
	{
		 if (flag.l == 1)
		 {
			ft_putendl(tmp->field);
		 }
		// gerer munki peut etre ? //version clem mais bancale peut etre
		else
		{
			split = (ft_strrchr(tmp->arg, '/') + 1); //opti
			if (split != NULL)
				ft_putendl(split);
			else
				ft_putendl(tmp->arg); // Mis en protection
		}
		tmp = tmp->next;
	}
}

void	alone(t_args **args, t_flags flag, t_numbers numbers)
{
	t_args	*tmp;
	int		arguments;
	(void)flag;

	arguments = 1;

	alone_2(*args, flag); //Affiche les non-ouvrables

	tmp = *args; //Affiche les ouvrables
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
