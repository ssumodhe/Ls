/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_field_3_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 17:46:07 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 21:28:37 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_put_perm(char *field, t_args *tmp)
{
	field[1] = (((tmp->lstat.st_mode & S_IRUSR) == S_IRUSR) ? 'r' : '-');
	field[2] = (((tmp->lstat.st_mode & S_IWUSR) == S_IWUSR) ? 'w' : '-');
	field[3] = (((tmp->lstat.st_mode & S_IXUSR) == S_IXUSR) ? 'x' : '-');
	field[4] = (((tmp->lstat.st_mode & S_IRGRP) == S_IRGRP) ? 'r' : '-');
	field[5] = (((tmp->lstat.st_mode & S_IWGRP) == S_IWGRP) ? 'w' : '-');
	field[6] = (((tmp->lstat.st_mode & S_IXGRP) == S_IXGRP) ? 'x' : '-');
	field[7] = (((tmp->lstat.st_mode & S_IROTH) == S_IROTH) ? 'r' : '-');
	field[8] = (((tmp->lstat.st_mode & S_IWOTH) == S_IWOTH) ? 'w' : '-');
	field[9] = (((tmp->lstat.st_mode & S_IXOTH) == S_IXOTH) ? 'x' : '-');
	field[10] = ' ';
	field[11] = ' ';
}

void	ft_put_ext_perm(char *field, t_args *tmp)
{
	char	current_usr;
	char	current_grp;
	char	current_oth;

	current_usr = field[3];
	current_grp = field[6];
	current_oth = field[9];
	field[3] = (((tmp->lstat.st_mode & S_ISUID) == S_ISUID) ? \
		's' : current_usr);
	field[6] = (((tmp->lstat.st_mode & S_ISGID) == S_ISGID) ? \
		's' : current_grp);
	field[9] = (((tmp->lstat.st_mode & S_ISVTX) == S_ISVTX) ? \
		't' : current_oth);
}

void	ft_put_hardlink(char *field, t_args *tmp, int i)
{
	int		n_hlink;

	n_hlink = tmp->info.hard_link;
	if (n_hlink == 0)
		field[i--] = '0';
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

void	ft_put_usr(char *field, char *usr, int end)
{
	int		i;

	i = 0;
	if (usr != NULL)
	{
		i = ft_strlen(usr);
		ft_strcpy(field, usr);
	}
	while (i != end)
	{
		field[i] = ' ';
		i++;
	}
}

void	ft_put_grp(char *field, char *grp, int end)
{
	int		i;

	i = 0;
	if (grp != NULL)
	{
		i = ft_strlen(grp);
		ft_strcpy(field, grp);
	}
	while (i != end)
	{
		field[i] = ' ';
		i++;
	}
}
