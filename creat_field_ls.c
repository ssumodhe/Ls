/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_field_ls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:01:43 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 17:53:20 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_get_info_item(t_args *tmp)
{
	tmp->info.hard_link = (int)(tmp->lstat.st_nlink);
	tmp->pwuid = getpwuid(tmp->lstat.st_uid);
	if (tmp->pwuid != NULL)
		tmp->info.usr = ft_strdup(tmp->pwuid->pw_name);
	else
		tmp->info.usr = ft_strdup("");
	tmp->grgid = getgrgid(tmp->lstat.st_gid);
	if (tmp->grgid != NULL)
		tmp->info.grp = ft_strdup(tmp->grgid->gr_name);
	else
		tmp->info.grp = ft_strdup("");
	tmp->info.size = (int)(tmp->lstat.st_size);
	tmp->info.link = NULL;
	if (S_ISCHR(tmp->lstat.st_mode) != 0 || S_ISBLK(tmp->lstat.st_mode) != 0)
	{
		tmp->info.maj = major(tmp->lstat.st_rdev);
		tmp->info.min = minor(tmp->lstat.st_rdev);
	}
	else
	{
		tmp->info.maj = 0;
		tmp->info.min = 0;
	}
}

char	ft_get_filetype(t_args *tmp)
{
	char	c;

	c = '\0';
	if (S_ISREG(tmp->lstat.st_mode) != 0)
		c = '-';
	else if (S_ISDIR(tmp->lstat.st_mode) != 0)
		c = 'd';
	else if (S_ISCHR(tmp->lstat.st_mode) != 0)
		c = 'c';
	else if (S_ISBLK(tmp->lstat.st_mode) != 0)
		c = 'b';
	else if (S_ISFIFO(tmp->lstat.st_mode) != 0)
		c = 'p';
	else if (S_ISLNK(tmp->lstat.st_mode) != 0)
		c = 'l';
	else if (S_ISSOCK(tmp->lstat.st_mode) != 0)
		c = 's';
	return (c);
}

char	*ft_create_field(int n, t_args *tmp, t_max max) // A METTRE A LA NORME
{
	char	*field;
	int		i;

	if (!(field = (char *)malloc(sizeof(char) * n + 1)))
		return (NULL);
	field[n] = '\0';
	i = 0;
	field[0] = ft_get_filetype(tmp);
	ft_put_perm(field, tmp);
	ft_put_ext_perm(field, tmp, 3, 6, 9);
	ft_put_hardlink(field, tmp, 11 + max.hard_link);
	field[11 + max.hard_link + 1] = ' ';
	i = 11 + max.hard_link + 2;
	ft_put_usr(field + i, tmp->info.usr, max.usr);
	i = 11 + max.hard_link + 2 + max.usr;
	field[i++] = ' ';
	field[i++] = ' ';
	ft_put_grp(field + i, tmp->info.grp, max.grp);
	i = 11 + max.hard_link + 2 + max.usr + 1 + max.grp;
	field[++i] = ' ';
	field[++i] = ' ';
	ft_put_size(field, tmp, i, max.size);
	i = i + max.size + 1;
	field[i++] = ' ';
	ft_put_time(field + i, tmp);
	i = i + 12;
	field[i++] = ' ';
	if (ft_strrchr(tmp->arg, '/') != NULL)
		ft_strcpy(field + i, (ft_strrchr(tmp->arg, '/') + 1));
	else
		ft_strcpy(field + i, tmp->arg);
	if (S_ISLNK(tmp->lstat.st_mode) != 0)
	{
		if (ft_strrchr(tmp->arg, '/') != NULL)
			i = i + ft_strlen((ft_strrchr(tmp->arg, '/') + 1));
		else
			i = i + ft_strlen(tmp->arg);
		field[i++] = ' ';
		field[i++] = '-';
		field[i++] = '>';
		field[i++] = ' ';
		ft_strcpy(field + i, tmp->info.link);
	}
	return (field);
}

