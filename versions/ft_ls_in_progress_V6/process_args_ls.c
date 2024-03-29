/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args_ls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:04:06 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/31 20:27:47 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	all_args(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		if (tmp->bellow != NULL)
		{
			tmp->bellow = ft_mergesort(tmp->bellow, ft_ascii_mergesort);
//			all_args(&tmp->bellow); //pour -R + mettre autre fonction tri
		}
		tmp = tmp->next;
	}
}

void	put_args(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		ft_putendl(tmp->arg);
		if (tmp->bellow != NULL)
			put_args(&tmp->bellow);
		tmp = tmp->next;
	}
}

char	*ft_strjoin_by(char *str1, char c, char *str2)
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

void		get_stat(t_args	*tmp)
{
	//errno = 0;
	if ((stat(tmp->arg, &tmp->stat)) == -1)
	{
		;
			//free + set NULL le tmp->stat
	}
	//tmp->error = errno; //errno = 13....;
}


void		get_link_stat(t_args	*tmp)
{
	//errno = 0;
	if((lstat(tmp->arg, &tmp->lstat)) == -1)
	{
		;
			//free + set NULL le tmp->stat
	}
	//tmp->error = errno; //errno = 13....;
	//ft_putendl("tmp->error = ");
	//ft_putnbr(tmp->error);
}

t_args *args_newlist(char *str, struct dirent *d)
{
	t_args	*new;

	if(!(new = (t_args *)malloc(sizeof(*new))))
		ft_exit(RED"error malloc bellow's list creation"RESET);
	new->error = 0;
	new->arg = ft_strjoin_by(str, '/', d->d_name);
	new->d_type = d->d_type; //on s'en tape
	get_stat(new);
	get_link_stat(new);
	new->bellow = NULL;
	new->next = NULL;
	new->prev = NULL;
	return(new);
}


void	ft_openfiles(t_args **args)
{
	DIR		*dir;
	struct dirent *d;
	t_args	*tmp;

	errno = 0;
	dir = NULL;
	if ((dir = opendir((*args)->arg)))
	{
		(*args)->error = errno;
		while ((d = readdir(dir)))
		{
			if ((*args)->bellow == NULL)
			{
				//free*/
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
	}
	else
		(*args)->error = errno;
	if (dir && closedir(dir) == -1)
		ft_exit("We seem to reach a probleme when closing the directory");
}

void	ft_openfiles_withouta(t_args **args)
{
	DIR		*dir;
	struct dirent *d;
	t_args	*tmp;
	int		i;

	errno = 0;
	dir = NULL;
	i = ft_strlen((*args)->arg);
	if (/*(*args)->arg[i] != '.' && */(dir = opendir((*args)->arg)))
	{
		(*args)->error = errno;
		while ((d = readdir(dir)))
		{
			if (d->d_name[0] != '.')
			{
				if ((*args)->bellow == NULL)
				{
					//free*/
					//(*args)->bellow = args_newlist((*args)->arg, d, errno);
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
		//		ft_putendl("ON A REUSSI");
//				if (d->d_name[0] != '.' && d->d_type == 4) // pour -R
//					ft_openfiles_withouta(&tmp);
			}
		}
	}
	else 
		(*args)->error = errno;
	
//	ft_putstr(HIGHLIGHT UNDERLINE GREEN ITALIC); //
//	ft_putstr((*args)->arg); //
//	ft_putstr("   error = "); //
//	ft_putnbr((*args)->error); //
//	ft_putendl(RESET""); //

	if (dir && closedir(dir) == -1)
		ft_exit("We seem to reach a probleme when closing the directory");
}

void	create_bellow(t_args **args, int opt_a)
{
		if (opt_a == 1)
			ft_openfiles(args);
		else 
			ft_openfiles_withouta(args);
		all_args(args); //Tri ascii par mergesort
}

void	process_args(t_args **args, int opt_a)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		create_bellow(&tmp, opt_a);	
		tmp = tmp->next;
	}
	all_args(args); //Tri ascii par mergesort
}
