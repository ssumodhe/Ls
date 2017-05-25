/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_r_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 19:00:13 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/25 21:12:52 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_r(t_args **args)
{
	t_args	*tmp;
	t_args	*before;
	t_args	*tmp_2;
	int		i;

	i = 0;
	tmp = *args;
	tmp->prev = NULL;
	before = tmp;
	tmp = tmp->next;

	while (tmp->next != NULL)
	{
		i++;
		tmp->prev = before;
		before = tmp;
		tmp = tmp->next;
	}
	if (i != 0)
		tmp->prev = before;

	tmp_2 = tmp;
	before = tmp_2;
	while (tmp->prev != NULL)
	{
		tmp_2 = tmp;
		tmp_2->next = tmp->prev;
		tmp_2 = tmp_2->next;
		tmp = tmp->prev;
	}
	tmp_2 = tmp;
	tmp_2->next = NULL;
	tmp = *args;
	*args = before;
}

/*
void	opt_r(t_args **args)
{
	t_args	*tmp;
	t_args	*before;
	t_args	*tmp_2;
	int		i;

	i = 0;
	tmp = *args;
	tmp->prev = NULL;
	before = tmp;
	tmp = tmp->next;
	while (tmp->next != NULL)
	{
		i++;
		tmp->prev = before;
		before = tmp;
		tmp = tmp->next;
	}
	if (i != 0)
		tmp->prev = before;

	tmp_2 = tmp;
	before = tmp_2;
	while (tmp->prev != NULL)
	{
		tmp_2 = tmp;
		tmp_2 = tmp_2->next;
		tmp = tmp->prev;
	}
	tmp = *args;
	*args = before;
}
*/
