/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 17:17:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/03 23:45:03 by ssumodhe         ###   ########.fr       */
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

void	ft_get_info_item(t_args *tmp)
{
	tmp->info.hard_link = (int)(tmp->lstat.st_nlink);
	tmp->pwuid = getpwuid(tmp->lstat.st_uid);
	tmp->info.usr = ft_strdup(tmp->pwuid->pw_name);
	tmp->grgid = getgrgid(tmp->lstat.st_gid);
	tmp->info.grp = ft_strdup(tmp->grgid->gr_name);
	tmp->info.size = (int)(tmp->lstat.st_size);
	tmp->info.link = NULL;

	ft_putstr(ITALIC PURPLE);
	ft_putstr("~~~~~~~~~~ ");
	ft_putstr(tmp->arg);
	ft_putendl(": ~~~~~~~~~~");
	ft_putstr("nb hard link = ");
	ft_putnbr(tmp->info.hard_link);
	ft_putstr("\nuser's name  = ");
	ft_putstr(tmp->info.usr);
	ft_putstr("\ngroup's name = ");
	ft_putstr(tmp->info.grp);
	ft_putstr("\n\tsize = ");
	ft_putnbr(tmp->info.size);

	ft_putendl("");
	ft_putstr(RESET);

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

void	ft_put_hardlink(char *field, t_args *tmp, int i)
{
	int		n_hlink;

	n_hlink = tmp->info.hard_link;
	while (n_hlink > 0)
	{
		field[i] = '0' + (n_hlink % 10);
		n_hlink = n_hlink / 10;
		i--;
	}
	if (i != 11)
	{
		while (i != 11)
		{
			field[i] = ' ';
			i--;
		}
	}
	
}

char	*ft_create_field(int n, t_args *tmp, t_max max)
{
	char	*field;
	int		i;
	
	field = (char *)malloc(sizeof(char) * n + 1); //
//	ft_memset(field, 65, n + 1);
	field[n] = '\0';

	i = 0;
	field[0] = ft_get_filetype(tmp);
	//owner
	field[1] = (((tmp->lstat.st_mode & S_IRUSR) == S_IRUSR) ? 'r' : '-');
	field[2] = (((tmp->lstat.st_mode & S_IWUSR) == S_IWUSR) ? 'w' : '-');
	field[3] = (((tmp->lstat.st_mode & S_IXUSR) == S_IXUSR) ? 'x' : '-');
	//group
	field[4] = (((tmp->lstat.st_mode & S_IRGRP) == S_IRGRP) ? 'r' : '-');
	field[5] = (((tmp->lstat.st_mode & S_IWGRP) == S_IWGRP) ? 'w' : '-');
	field[6] = (((tmp->lstat.st_mode & S_IXGRP) == S_IXGRP) ? 'x' : '-');
	//others
	field[7] = (((tmp->lstat.st_mode & S_IROTH) == S_IROTH) ? 'r' : '-');
	field[8] = (((tmp->lstat.st_mode & S_IWOTH) == S_IWOTH) ? 'w' : '-');
	field[9] = (((tmp->lstat.st_mode & S_IXOTH) == S_IXOTH) ? 'x' : '-');
	field[10] = ' '; //Si bonus attributs
	field[11] = ' ';
	ft_put_hardlink(field, tmp, 11 + max.hard_link);
	field[11 + max.hard_link + 1] = ' ';
	i = 11 + max.hard_link + 2;
	ft_strcpy(field + i, tmp->info.usr);
	i = 11 + max.hard_link + 2 + max.usr;
	field[i] = ' ';
	i++;
	ft_strcpy(field + i, tmp->info.grp);
	i = 11 + max.hard_link + 2 + max.usr + 1 + max.grp;
	field[i] = '|';


	return (field);
}

void	all_args_opt_l(t_args *args)
{
	t_max	max;
	t_args	*tmp;
	int		n;

	max = ft_init_max();
	tmp = args;
	while (tmp)
	{
		ft_get_info_item(tmp);
		max = ft_cmp_max(tmp, max);
		tmp = tmp->next;
	}

	// on boucle UNIQUEMENT sur la liste chainée = on ne passeuh PAS dans les bellow
	// on recup les infos necessaires (pour t_max ? ou pour tous?)
	// on remplit t_max.
	// on repasse dans la liste chainée : on malloc et on remplit field
	
	ft_putstr(CYAN HIGHLIGHT);
	ft_putendl("=== Struct Max ===");
	ft_putstr("hard_link = ");
	ft_putnbr(max.hard_link);
	ft_putstr("\nuser len = ");
	ft_putnbr(max.usr);
	ft_putstr("\ngrp len  = ");
	ft_putnbr(max.grp);
	ft_putstr("\nsize = ");
	ft_putnbr(max.size);

	ft_putendl("");
	ft_putstr(RESET);

	char	*buff_read;
	int		len_read;



	buff_read = NULL;
	tmp = args;
	while (tmp)
	{
		n = (10 + 2 + max.hard_link + 1 + max.usr + 2 + max.grp + 2 \
			+ max.size + 1 + 12 + 1 \
			+ ft_strlen((ft_strrchr(tmp->arg, '/') + 1)));
		if ((len_read = readlink(tmp->arg, buff_read, sizeof(buff_read) - 1)) != -1)
		{
			tmp->info.link = (ft_strrchr(buff_read, '/') + 1);
			n = n + 3 + ft_strlen(tmp->info.link);
		}
		tmp->field = ft_create_field(n, tmp, max); //
		ft_strdel(&buff_read);
		tmp = tmp->next;
	}
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
