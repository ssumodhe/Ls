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
	struct s_merge 		*next;
}					t_merge;


void	ft_split_mergesort(t_merge **merge, int size_lst)
{
	t_merge	*left;
	t_merge	*right;
	t_merge	*tmp;
	int		i;

	i = 0;
	right = *merge;
	while (i < (size_lst / 2) - 1)
	{
		right = right->next;
		i++;
	}
	left = right->next;
	right->next = NULL;
	right = *merge;

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

}


int		ft_count_lst(t_merge **merge)
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
	merge->i = ft_atoi(argv[1]);
	merge->next = NULL;

	i = 2;
	while (i < argc)
	{
		if (!(new = (t_merge *)malloc(sizeof(*new))))
			ft_exit(RED"error malloc t_merge *merge"RESET);
		new->i = ft_atoi(argv[i]);
		new->next = NULL;

		tmp = merge;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;

		i++;
	}

	i = ft_count_lst(&merge);
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

	ft_split_mergesort(&merge, i);

	return (0);
}
