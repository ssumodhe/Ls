/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_t_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:37:21 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/18 19:59:30 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	date_modif_sort_args(t_args **args)
{
	t_args	*tmp;
	t_args	*after;
	t_args	*prev;

	prev = NULL;
	tmp = *args;
	while (tmp)
	{
		if (tmp->next != NULL && (tmp->stat.st_mtimespec.tv_sec < tmp->next->stat.st_mtimespec.tv_sec))
		{
			after = tmp->next;
			if (prev)
				prev->next = after;
			else
				*args = after;
			tmp->next = after->next;
			after->next = tmp;
			date_modif_sort_args(args);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/*
void	all_args_modif(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		date_modif_sort_args(&tmp);
		if (tmp->bellow != NULL)
		{
			//date_modif_sort_args(&tmp->bellow);
			all_args_modif(&tmp->bellow);
		}
		tmp = tmp->next;
	}
}
*/

void	opt_t(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
	//	if (!(tmp->stat = (struct stat *)malloc(sizeof(*tmp->stat))))
	//		ft_exit(RED"error malloc stat"RESET);
		errno = 0;
		if((lstat(tmp->arg, &tmp->stat)) == -1)
		{
			ft_putstr_fd("lstat error :", 2);
			perror(tmp->arg);
			//free + set NULL le tmp->stat
		}
		printf(GREEN"OPT_T | arg = %s, date modif = %ld\n"RESET, tmp->arg, tmp->stat.st_mtimespec.tv_sec);
		//printf(GREEN"arg = %s\t%s"RESET, tmp->arg, ctime(&tmp->stat.st_mtimespec.tv_sec));
		if (tmp->bellow != NULL)
			opt_t(&tmp->bellow);
		tmp = tmp->next;
	}


//	all_args_modif(args);
	date_modif_sort_args(args);

	ft_putstr(RESET); //
}

/*
void	opt_t(t_args **args)
{
	t_args	*tmp;
	struct stat *stat;

	tmp = *args;
	if (!(stat = (struct stat *)malloc(sizeof(*stat))))
		ft_exit(RED"error malloc stat"RESET);
	while (tmp)
	{
		errno = 0;
		if((lstat(tmp->arg, stat)) == -1)
		{
			ft_putstr_fd("lstat error :", 2);
			perror(tmp->arg);
		}
		// if (bellow);
		// opt_t;
		printf(GREEN"OPT_T | arg = %s, date modif = %ld\n"RESET, tmp->arg, stat->st_mtimespec.tv_sec);
		tmp = tmp->next;
	}


}*/
