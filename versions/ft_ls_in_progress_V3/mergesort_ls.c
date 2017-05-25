/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 12:10:18 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/25 15:48:44 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_modif_date_mergesort(t_args **tmp, t_args **left, t_args **right)
{
	if ((*left)->stat.st_mtimespec.tv_sec > (*right)->stat.st_mtimespec.tv_sec)
	{
		*tmp = *left;
		*left = (*left)->next;
	}
	else
	{
		*tmp = *right;
		*right = (*right)->next;
	}
}

void	ft_ascii_mergesort(t_args **tmp, t_args **left, t_args **right)
{
	if ((ft_strcmp((*left)->arg, (*right)->arg)) < 0)
	{
		*tmp = *left;
		*left = (*left)->next;
	}
	else
	{
		*tmp = *right;
		*right = (*right)->next;
	}
}

void	ft_descendingorder_mergesort(t_args **tmp, t_args **left, t_args **right)
{
	if ((*left)->i > (*right)->i)
	{
		*tmp = *left;
		*left = (*left)->next;
	}
	else
	{
		*tmp = *right;
		*right = (*right)->next;
	}
}

int		ft_lstcount(t_args **merge)
{
	t_args	*tmp;
	int		nb_list;

	nb_list = 0;
	tmp = *merge;
	while (tmp)
	{
		nb_list++;
		tmp = tmp->next;
	}
	return (nb_list);
}

t_args *ft_glue_mergesort(t_args *left, t_args *right, void	f())
{
	t_args		*tmp;
	t_args		*head;
	t_args		*tail;

	head = NULL;
	while (left || right)
	{
		if (!left)
		{
			tmp = right;
			right = right->next;
		}
		else 
		{
			if (!right)
			{
				tmp = left;
				left = left->next;
			}
			else
				f(&tmp, &left, &right);
		}
		if (!head)
			head = tmp;
		else
			tail->next = tmp;
		tail = tmp;
	}
	return (head);
}

t_args	*ft_mergesort(t_args *merge, void f())
{
	t_args	*left;
	t_args	*right;
//	t_args	*tmp; //
	int		i;
	int		nb_list;

	if (merge->next == NULL)
		return (merge);
	i = 0;
	nb_list = ft_lstcount(&merge);
	left = merge;
	while (i < (nb_list / 2) - 1)
	{
		left = left->next;
		i++;
	}
	right = left->next;
	left->next = NULL;
	left = merge;
/*
//AFFICHAGE/
ft_putendl(GREEN"RIGHT"RESET);

	tmp = right;
	while (tmp != NULL)
	{
		ft_putstr(tmp->arg);
		if (tmp->next != NULL)
			ft_putstr("\t");
		tmp = tmp->next;gg
	}
	ft_putendl("");
ft_putendl(GREEN"LEFT"RESET);

	tmp = left;
	while (tmp != NULL)
	{
		ft_putstr(tmp->arg);
		if (tmp->next != NULL)
			ft_putstr("\t");
		tmp = tmp->next;
	}
	ft_putendl("");
//END - AFFICHAGE/
*/
	right = ft_mergesort(right, f);
	left = ft_mergesort(left, f);
//	ft_putendl("JE SORS");
	return ((ft_glue_mergesort(left, right, f)));
}


/*
int		main(int argc, char **argv)
{
	t_args		*merge;
	t_args		*tmp;
	t_args		*new;
	int			i;

	if (argc == 1)
		return (-1);

	if (!(merge = (t_args *)malloc(sizeof(*merge))))
		ft_exit(RED"error malloc t_args *merge"RESET);
//	merge->i = ft_atoi(argv[1]);
	merge->str = ft_strdup(argv[1]);
	merge->next = NULL;

	i = 2;
	while (i < argc)
	{
		if (!(new = (t_args *)malloc(sizeof(*new))))
			ft_exit(RED"error malloc t_args *merge"RESET);
//		new->i = ft_atoi(argv[i]);
		new->str = ft_strdup(argv[i]);
		new->next = NULL;

		tmp = merge;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;

		i++;
	}

	i = ft_lstcount(&merge);
	ft_putstr("Nombre de liste : ");
	ft_putnbr(i);
	ft_putendl("");

ft_putendl(GREEN"AVANT"RESET);

	tmp = merge;
	while (tmp != NULL)
	{
		ft_putstr(tmp->arg);
		if (tmp->next != NULL)
			ft_putstr("\t");
		tmp = tmp->next;
	}
	ft_putendl("");

	merge = mergesort(merge);
	
ft_putendl(GREEN"APRES"RESET);

	tmp = merge;
	while (tmp != NULL)
	{
		ft_putstr(tmp->arg);
		if (tmp->next != NULL)
			ft_putstr("\t");
		tmp = tmp->next;
	}
	ft_putendl("");

	return (0);
}*/
