/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 12:10:18 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 03:02:56 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_modif_date_mergesort(t_args **tmp, t_args **left, t_args **right)
{
	if ((*left)->lstat.st_mtimespec.tv_sec >= (*right)->lstat.st_mtimespec.tv_sec)
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
/*
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
*/
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

t_args *ft_glue_mergesort(t_args *left, t_args *right, void	f()) // A METTRE A LA NORME
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
	right = ft_mergesort(right, f);
	left = ft_mergesort(left, f);
	return ((ft_glue_mergesort(left, right, f)));
}
