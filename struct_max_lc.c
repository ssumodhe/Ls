/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_max_lc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 22:33:23 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 22:36:15 by ssumodhe         ###   ########.fr       */
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
	if (max.hard_link < ft_intlen(tmp->info.hard_link))
		max.hard_link = ft_intlen(tmp->info.hard_link);
	if (max.usr < (int)ft_strlen(tmp->info.usr))
		max.usr = ft_strlen(tmp->info.usr);
	if (max.grp < (int)ft_strlen(tmp->info.grp))
		max.grp = ft_strlen(tmp->info.grp);
	if (S_ISCHR(tmp->lstat.st_mode) != 0 || S_ISBLK(tmp->lstat.st_mode) != 0)
	{
		if (max.size < 8)
			max.size = 8;
	}
	else
	{
		if (max.size < ft_intlen(tmp->info.size))
			max.size = ft_intlen(tmp->info.size);
	}
	return (max);
}
