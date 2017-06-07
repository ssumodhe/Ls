/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_field_2_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:21:52 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 23:53:53 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_size_put_maj(char *field, t_args *tmp, int start)
{
	int		i;
	int		n_m;

	n_m = tmp->info.maj;
	i = start + ft_intlen(n_m);
	field[i + 1] = ',';
	if (n_m == 0)
		field[i--] = '0';
	while (n_m > 0)
	{
		field[i] = '0' + (n_m % 10);
		n_m = n_m / 10;
		i--;
	}
}

void	ft_size_maj_min(char *field, t_args *tmp, int start, int end)
{
	int		i;
	int		n_m;

	i = start + end;
	n_m = tmp->info.min;
	if (n_m == 0)
		field[i--] = '0';
	while (n_m > 0)
	{
		field[i] = '0' + (n_m % 10);
		n_m = n_m / 10;
		i--;
	}
	while (i != start)
	{
		field[i] = ' ';
		i--;
	}
	ft_size_put_maj(field, tmp, start);
}

void	ft_put_size(char *field, t_args *tmp, int start, int end)
{
	int		i;
	int		n_size;

	i = start + end;
	n_size = tmp->info.size;
	if (S_ISCHR(tmp->lstat.st_mode) != 0 || S_ISBLK(tmp->lstat.st_mode) != 0)
		ft_size_maj_min(field, tmp, start, end);
	else
	{
		if (n_size == 0)
			field[i--] = '0';
		while (n_size > 0)
		{
			field[i] = '0' + (n_size % 10);
			n_size = n_size / 10;
			i--;
		}
		while (i != start)
		{
			field[i] = ' ';
			i--;
		}
	}
}

void	ft_put_time(char *field, t_args *tmp)
{
	int		i;
	int		j;
	char	*date_year;

	i = 0;
	j = 4;
	date_year = ctime(&tmp->lstat.st_mtime);
	if (date_year != NULL)
	{
		while (i < 12)
			field[i++] = date_year[j++];
		if (((time(0) - tmp->lstat.st_mtime) > 15778800) \
				|| (time(0) < tmp->lstat.st_mtime))
		{
			j = 24;
			while (j > 19)
				field[--i] = date_year[--j];
			field[i] = ' ';
		}
	}
	else
		while (i < 12)
			field[i++] = ' ';
}
