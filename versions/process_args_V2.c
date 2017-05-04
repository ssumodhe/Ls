/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_args_ls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 17:04:06 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/04 17:49:01 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
void	ascii_sort_args(t_args **args)
{
	t_args	*tmp;
	t_args	*after;
	t_args	*prev;

	prev = NULL;
	tmp = *args;
	while (tmp)
	{
		if (tmp->next != NULL && (ft_strcmp(tmp->arg, tmp->next->arg) > 0))
		{
			after = tmp->next;
			if (prev)
				prev->next = after;
			else
				*args = after;
			tmp->next = after->next;
			after->next = tmp;
			ascii_sort_args(args);
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
/*
void	ascii_sort_args(t_args **args)
{
	t_args	*tmp;
	t_args	*tmp_2;
	t_args	*swap;
	t_args	*prev;

	prev = NULL;
	tmp = *args;
	while (tmp)
	{
		ft_putstr(GREEN); //
		ft_putendl("les deux args sont:"); //
		ft_putendl(tmp->arg); //
		ft_putendl(tmp->next->arg); //
		ft_putstr(GREEN);  //
		if (tmp->next != NULL && (ft_strcmp(tmp->arg, tmp->next->arg) > 0))
		{
		ft_putnbr(ft_strcmp(tmp->arg, tmp->next->arg));
			ft_putchar(' ');
		ft_putstr(tmp->arg); //
			ft_putchar(' ');
		ft_putstr(tmp->next->arg); //
			ft_putchar(' ');
		ft_putendl(GREEN HIGHLIGHT"J'ai un swap a faire"RESET); //
	
			if (prev)
				prev->next = tmp->next;
			else
				*args = tmp->next;
			swap = tmp;
			tmp = tmp->next;
			tmp->next = swap;
			swap->next = tmp->next->next;


			tmp_2 = *args;
			while (tmp_2)
			{
				ft_putendl(tmp_2->arg); //
				tmp_2 = tmp_2->next;
			}
				ascii_sort_args(args);
		}
		prev = tmp;
		tmp = tmp->next;
	}

}
*/
void	all_args(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		ft_putendl(tmp->arg);
		if (tmp->bellow != NULL)
		{
			ascii_sort_args(&tmp->bellow);
			all_args(&tmp->bellow);
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
	(*args)->bellow = bellow;
	i = ft_strlen((*args)->arg);
	if ((*args)->arg[i] != '.' && (dir = opendir((*args)->arg)))
	{
		while ((d = readdir(dir)))
		{
			if (bellow == NULL)
			{
				if(!(bellow = (t_args *)malloc(sizeof(*bellow))))
					ft_exit(RED"error malloc bellow's list creation"RESET);
				bellow->arg = ft_strjoin_path((*args)->arg, '/', d->d_name);
				bellow->d = d;
				bellow->bellow = NULL;
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
				new->bellow = NULL;
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
	put_args(args);
	all_args(args);
/*	tmp = *args;
	while (tmp)
	{
		if (tmp->bellow)
			ascii_sort_args(&tmp->bellow);
		tmp = tmp->next;
	}*/
	ft_putstr(YELLOW); //
	put_args(args);
	ft_putstr(RESET); //

	//trier les bellow par ordre ascii
}
