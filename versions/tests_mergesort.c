/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_mergesort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 14:33:41 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/23 18:28:19 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

typedef struct		s_merge
{
	int					i;
	char *str;
	struct s_merge 		*next;
}					t_merge;

int		ft_lstcount(t_merge **merge)
{
	t_merge	*tmp;
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

void	ft_ascii_mergesort(t_merge **tmp, t_merge **left, t_merge **right)
{
	if ((ft_strcmp(left->str, right->str)) > 0)
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

void	ft_descendingorder_mergesort(t_merge **tmp, t_merge **left, t_merge **right)
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

t_merge *ft_glue_mergesort(t_merge *left, t_merge *right)
{
	t_merge		*tmp;
	t_merge		*head;
	t_merge		*tail;

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
				ft_descendingorder_mergesort(&tmp, &left, &right);
		}
		if (!head)
			head = tmp;
		else
			tail->next = tmp;
		tail = tmp;
	}
	return (head);
}

t_merge	*ft_split_mergesort(t_merge *merge)
{
	t_merge	*left;
	t_merge	*right;
	t_merge	*tmp; //
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

//AFFICHAGE/
ft_putendl(GREEN"RIGHT"RESET);

	tmp = right;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->i);
		if (tmp->next != NULL)
			ft_putstr("\t");
		tmp = tmp->next;
	}
	ft_putendl("");
ft_putendl(GREEN"LEFT"RESET);

	tmp = left;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->i);
		if (tmp->next != NULL)
			ft_putstr("\t");
		tmp = tmp->next;
	}
	ft_putendl("");
//END - AFFICHAGE/

	right = ft_split_mergesort(right);
	left = ft_split_mergesort(left);
	ft_putendl("JE SORS");
	return ((ft_glue_mergesort(left, right)));
}






int		main(int argc, char **argv)
{
	t_merge		*merge;
	t_merge		*tmp;
	t_merge		*new;
	int			i;

	if (argc == 1)
		return (-1);

	if (!(merge = (t_merge *)malloc(sizeof(*merge))))
		ft_exit(RED"error malloc t_merge *merge"RESET);
//	merge->i = ft_atoi(argv[1]);
	merge->str = ft_strdup(argv[1]);
	merge->next = NULL;

	i = 2;
	while (i < argc)
	{
		if (!(new = (t_merge *)malloc(sizeof(*new))))
			ft_exit(RED"error malloc t_merge *merge"RESET);
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
		ft_putnbr(tmp->i);
		if (tmp->next != NULL)
			ft_putstr("\t");
		tmp = tmp->next;
	}
	ft_putendl("");

	merge = ft_split_mergesort(merge);
	
ft_putendl(GREEN"APRES"RESET);

	tmp = merge;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->i);
		if (tmp->next != NULL)
			ft_putstr("\t");
		tmp = tmp->next;
	}
	ft_putendl("");

	return (0);
}
