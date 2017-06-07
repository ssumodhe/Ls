/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 17:17:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 17:53:25 by ssumodhe         ###   ########.fr       */
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

int		all_args_opt_l(t_args *args)
{
	t_max	max;
	t_args	*tmp;
	int		total;
	int		n;

	max = ft_init_max();
	tmp = args;
	total = 0;
	while (tmp)
	{
		total = total + tmp->lstat.st_blocks;
		ft_get_info_item(tmp);
		max = ft_cmp_max(tmp, max);
		tmp = tmp->next;
	}
	char	buff_read[256];
	int		len_read;
	tmp = args;

	while (tmp)
	{
		n = (10 + 2 + max.hard_link + 1 + max.usr + 2 + max.grp + 2 \
				+ max.size + 1 + 12 + 1);
		if (ft_strrchr(tmp->arg, '/') != NULL)
			n = n + ft_strlen((ft_strrchr(tmp->arg, '/') + 1));
		else
			n = n + ft_strlen(tmp->arg) + 1;
		if (S_ISLNK(tmp->lstat.st_mode) != 0 && (len_read = readlink(tmp->arg, buff_read, 256)))
		{
			buff_read[len_read] = '\0';
			tmp->info.link = ft_strdup(buff_read);
			if (tmp->info.link != NULL)
				n = n + 4 + ft_strlen(tmp->info.link);
			else
				n = n + 4 + 50;
		}
		tmp->field = ft_create_field(n, tmp, max); 
		tmp = tmp->next;
	}
	return (total);
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
			(*args)->l_total = all_args_opt_l(tmp->bellow);
		tmp = tmp->next;
	}
}
