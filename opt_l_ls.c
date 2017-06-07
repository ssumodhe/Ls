/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 17:17:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 22:39:16 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_n_if_link(t_args *tmp, int n)
{
	if (tmp->info.link != NULL)
		n = n + 4 + ft_strlen(tmp->info.link);
	else
		n = n + 4 + 50;
	return (n);
}

void	ft_opt_l_field(t_args *args, t_max max)
{
	t_args	*tmp;
	int		n;
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
		if (S_ISLNK(tmp->lstat.st_mode) != 0 && \
				(len_read = readlink(tmp->arg, buff_read, 256)))
		{
			buff_read[len_read] = '\0';
			tmp->info.link = ft_strdup(buff_read);
			n = ft_n_if_link(tmp, n);
		}
		tmp->field = ft_create_field(n, tmp, max);
		tmp = tmp->next;
	}
}

int		all_args_opt_l(t_args *args)
{
	t_max	max;
	t_args	*tmp;
	int		total;

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
	ft_opt_l_field(args, max);
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
