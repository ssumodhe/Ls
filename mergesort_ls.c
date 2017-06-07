/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_ls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 12:10:18 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 21:32:55 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_lstcount(t_args **merge)
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

void		ft_put_side(t_args **tmp, t_args **side)
{
	*tmp = *side;
	*side = (*side)->next;
}

t_args		*ft_glue_mergesort(t_args *left, t_args *right, void f())
{
	t_args		*tmp;
	t_args		*head;
	t_args		*tail;

	head = NULL;
	while (left || right)
	{
		if (!left)
			ft_put_side(&tmp, &right);
		else
		{
			if (!right)
				ft_put_side(&tmp, &left);
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

t_args		*ft_mergesort(t_args *merge, void f())
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
