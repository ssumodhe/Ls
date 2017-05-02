/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args_ls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:04:06 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/02 18:06:47 by ssumodhe         ###   ########.fr       */
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
	char	*both;
	t_args	*bellow;


	bellow = NULL;
	if ((dir = opendir(args->arg)))
	{
		printf(RESET"opening file %s\n"RESET, str);
		while ((d = readdir(dir)))
		{
			printf(GREEN"fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n", d->d_fileno, d->d_reclen, d->d_type, d->d_namlen, d->d_name);
			if (bellow == NULL)
			{
				if(!(bellow = (t_args *)malloc(sizeof(*bellow))))
					ft_exit(RED"error malloc bellow's list creation"RESET);
				bellow->args = ft_strdup(d->d_name);
				bellow->d = d;
				args->bellow = bellow;
			}
			//else ajouter au bellow deja existant.

			if (d->d_name[0] != '.' && d->d_type == 4)
			{
				errno = 0;
				printf(YELLOW"name is %s\n", d->d_name);
				both = ft_strjoin_path(args->arg, '/' ,d->d_name);
				printf(RESET"name is %s\n"RESET, both);
				ft_openfiles(both); //renvoyer un t_args
				ft_strdel(&both);
			}
		}
		printf(RESET"closing file %s\n"RESET, str);

		if (closedir(dir) == -1)
			ft_exit("We seem to reach a probleme when closing the directory");
	}
}


void	process_args(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		ft_openfiles(&tmp)
			tmp = tmp->next;
	}
}
