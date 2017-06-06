/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_l_r_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 20:35:14 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/02 20:50:34 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	all_args_opt_r(t_args **args)
{
	t_args	*tmp;
	t_args	*before;
	t_args	*tmp_2;

	if (!args)
		return ;
	tmp = *args;
	before = NULL;
	while (tmp->next != NULL) //J'initialise les prev
	{
		tmp->prev = before;
		before = tmp;
		tmp = tmp->next;
	}
	tmp->prev = before;

	tmp_2 = tmp;
	before = tmp_2;
	while (tmp->prev != NULL) // Je reverse
	{
		tmp_2->next = tmp->prev;
		tmp_2 = tmp_2->next;
		tmp = tmp->prev;
	}
	tmp_2->next = NULL;
	tmp = *args;
	*args = before;
}

void	opt_l_r(t_args **args)
{
	t_args	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		if (tmp->bellow != NULL)
		{
			all_args_opt_r(&tmp->bellow);
			//opt_l_r(&tmp->bellow);
		}
		tmp = tmp->next;
	}
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
//	tmp->prev = NULL;
	before = NULL;
//	tmp = tmp->next;

	while (tmp->next != NULL)
	{
		i++;
		tmp->prev = before;
		before = tmp;
		tmp = tmp->next;
	}
//	if (i != 0)
		tmp->prev = before;

	tmp_2 = tmp;
	before = tmp_2;
	ft_putendl(RED); //
	ft_putendl(tmp->prev->arg); //
	ft_putendl(RESET); //
	while (tmp->prev != NULL)
	{
		ft_putendl(tmp->arg); //
//		tmp_2 = tmp;
		tmp_2->next = tmp->prev;
		tmp_2 = tmp_2->next;
		tmp = tmp->prev;
	}
//	tmp_2 = tmp;
	tmp_2->next = NULL;
	tmp = *args;
	*args = before;
}
*/
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
