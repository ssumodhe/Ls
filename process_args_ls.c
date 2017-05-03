/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args_ls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:04:06 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/03 15:43:41 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strjoin_path(char *str1, char c, char *str2)
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
	return(join);
}

void	ft_openfiles(t_args **args)
{
	DIR		*dir;
	struct dirent *d;
	t_args	*bellow;
	t_args	*tmp;
	t_args	*new;
	int		i;


	dir = NULL;
	bellow = NULL;

	i = ft_strlen((*args)->arg);
	while (i >= 0 && (*args)->arg[i] != '/')
		i--;
	i++;

	if ((*args)->arg[i] != '.' && (dir = opendir((*args)->arg)))
	{
		printf(RESET"opening file %s\n"RESET, (*args)->arg);
		while ((d = readdir(dir)))
		{
			printf(GREEN"fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n", d->d_fileno, d->d_reclen, d->d_type, d->d_namlen, d->d_name);
			if (bellow == NULL)
			{
				if(!(bellow = (t_args *)malloc(sizeof(*bellow))))
					ft_exit(RED"error malloc bellow's list creation"RESET);
				bellow->arg = ft_strjoin_path((*args)->arg, '/', d->d_name);
				bellow->d = d;
				bellow->next = NULL;
				(*args)->bellow = bellow; //free
				tmp = (*args)->bellow;
			}
			else
			{
				if(!(new = (t_args *)malloc(sizeof(*new))))
					ft_exit(RED"error malloc new-bellow's list creation"RESET);
				new->arg = ft_strjoin_path((*args)->arg, '/', d->d_name);
				new->d = d;
				new->next = NULL;
				tmp = (*args)->bellow;
				while (tmp->next != NULL)
					tmp = tmp->next;
				tmp->next = new;
				tmp = tmp->next;
			}
			if (d->d_name[0] != '.' && d->d_type == 4)
			{
				errno = 0;
				ft_openfiles(&tmp);
			}
		}
		printf(RESET"closing file %s\n"RESET, (*args)->arg);
	}
	if (dir && closedir(dir) == -1)
		ft_exit("We seem to reach a probleme when closing the directory");
}


void	process_args(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		ft_openfiles(&tmp);
		tmp = tmp->next;
	}
	//trier les bellow par ordre ascii
}
