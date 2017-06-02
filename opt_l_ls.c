/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 17:17:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/02 20:54:49 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_max	ft_init_max(void)
{
	t_max	max;

	max.hard_link = 0;
	max.usr = 0;
	max.grp = 0;
	max.size = 0;
	return (max);
}

t_max	ft_cmp_max(t_args *tmp, t_max max)
{
	if (max.hard_link < tmp->info.hard_link)
		max.hard_link = tmp->info.hard_link;
	if (max.usr < (int)ft_strlen(tmp->info.usr))
		max.usr = ft_strlen(tmp->info.usr);
	if (max.grp < (int)ft_strlen(tmp->info.grp))
		max.grp = ft_strlen(tmp->info.grp);
	if (S_ISCHR(tmp->lstat.st_mode) || S_ISBLK(tmp->lstat.st_mode))
	{
		if (max.size < 8)
			max.size = 8;
	}
	else
	{
		if (max.size < tmp->info.size)
			max.size = tmp->info.size;
	}
	return (max);
}

void	ft_get_info_item(t_args *tmp)
{
	tmp->info.hard_link = (int)(tmp->lstat.st_nlinks);
	tmp->info.usr = getpuid;
	tmp->info.grp = getgrpppd;
	tmp->info.size = (int)(tmp->lstat.st_size);
}

void	all_args_opt_l(t_args *args)
{
	t_max	max;
	t_args	*tmp;

	max = ft_init_max();

	tmp = args;
	while (tmp)
	{
		ft_get_info_item(tmp);
		max = ft_cmp_max(tmp, max);
		tmp = tmp->next;
	}
	// on boucle UNIQUEMENT sur la liste chainée = on ne passeuh PAS dans les bellow
	// on recup les infos necessaires (pour t_max ? ou pour tous ?)
	// on remplit t_max.
	// on repasse dans la liste chainée : on malloc et on remplit field
}

void	opt_l(t_args **args)
{
	t_args	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		if (tmp->bellow != NULL)
			all_args_opt_l(tmp->bellow);
		tmp = tmp->next;
	}
}
