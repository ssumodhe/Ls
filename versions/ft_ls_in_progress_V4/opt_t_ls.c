/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_t_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:37:21 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/26 20:39:04 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	all_args_opt_t(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		errno = 0;
		if((lstat(tmp->arg, &tmp->stat)) == -1)
		{
			ft_putstr_fd("ft_ls: ", 2);
			perror(tmp->arg);
			//free + set NULL le tmp->stat
		}
		//printf(GREEN"OPT_T | arg = %s, date modif = %ld\n"RESET, tmp->arg, tmp->stat.st_mtimespec.tv_sec);
		//printf(GREEN"OPT_T | arg = %s\t%s"RESET, tmp->arg, ctime(&tmp->stat.st_mtimespec.tv_sec));
//		if (tmp->bellow != NULL)
//			opt_t(&tmp->bellow);
		tmp = tmp->next;
	}

	*args = ft_mergesort(*args, ft_modif_date_mergesort);

	ft_putstr(RESET); //
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
