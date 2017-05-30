/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_t_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:37:21 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/30 20:16:07 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	all_args_opt_t(t_args **args)
{
/*	int		go;
	t_args	*tmp;

	tmp = *args;
	go = 1;
	while (tmp)
	{
		errno = 0;
		if((lstat(tmp->arg, &tmp->lstat)) == -1)
		{
			go = 0;
			tmp->error = errno; //errno = 13....;
			//free + set NULL le tmp->stat
		}
//			printf("opt_t | type = %hu\n", tmp->stat.st_mode); //
//		if (tmp->stat.st_mode == S_IFLNK)
//			ft_putendl(tmp->arg); //Ici... need les liens pour le deplacer dans la liste chainee a cote de son fichier pointe
			
		tmp = tmp->next;
	}*/


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
