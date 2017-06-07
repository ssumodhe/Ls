/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfiles_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 16:19:26 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 21:37:44 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*ft_strjoin_by(char *str1, char c, char *str2)
{
	int		n1;
	int		n2;
	int		a;
	int		b;
	char	*join;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	n1 = ft_strlen(str1);
	n2 = ft_strlen(str2);
	if (!(join = (char *)malloc(sizeof(char) * (n1 + n2 + 2))))
		return (NULL);
	join[n1 + n2 + 1] = '\0';
	a = 0;
	while (str1[a] != '\0')
	{
		join[a] = str1[a];
		a++;
	}
	join[a++] = c;
	b = 0;
	while (str2[b] != '\0')
		join[a++] = str2[b++];
	return (join);
}

t_args		*args_newlist(char *str, struct dirent *d)
{
	t_args	*new;

	if (!(new = (t_args *)malloc(sizeof(*new))))
		ft_exit(RED"error malloc bellow's list creation"RESET);
	new->error = 0;
	new->arg = ft_strjoin_by(str, '/', d->d_name);
	new->field = NULL;
	get_stat(new);
	get_link_stat(new);
	new->l_total = 0;
	new->bellow = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		ft_put_bellow_file(t_args **args, struct dirent *d)
{
	t_args	*tmp;

	if ((*args)->bellow == NULL)
	{
		(*args)->bellow = args_newlist((*args)->arg, d);
		tmp = (*args)->bellow;
	}
	else
	{
		tmp = (*args)->bellow;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = args_newlist((*args)->arg, d);
		tmp = tmp->next;
	}
}

void		ft_openfiles(t_args **args)
{
	DIR				*dir;
	struct dirent	*d;

	if (!args)
		return ;
	errno = 0;
	dir = NULL;
	if ((dir = opendir((*args)->arg)))
	{
		(*args)->error = errno;
		while ((d = readdir(dir)))
		{
			ft_put_bellow_file(args, d);
		}
	}
	else
		(*args)->error = errno;
	if (dir && closedir(dir) == -1)
		ft_exit(PB_CLOSE_DIR);
}

void		ft_openfiles_withouta(t_args **args)
{
	DIR				*dir;
	struct dirent	*d;

	if (!args)
		return ;
	errno = 0;
	dir = NULL;
	if ((dir = opendir((*args)->arg)))
	{
		(*args)->error = errno;
		while ((d = readdir(dir)))
		{
			if (d->d_name[0] != '.')
			{
				ft_put_bellow_file(args, d);
			}
		}
	}
	else
		(*args)->error = errno;
	if (dir && closedir(dir) == -1)
		ft_exit(PB_CLOSE_DIR);
}
