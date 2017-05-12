/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:14:40 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/12 19:40:39 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_option	*fill_option(int i, char *opt, t_option *option)
{
	t_option	*tmp;
	t_option	*new;

	if (!(new = (t_option *)malloc(sizeof(*new))))
		ft_exit(RED"error malloc option's list creation"RESET);
	if (option == NULL)
	{
		new->i = i;
		new->opt = ft_strdup(opt);
		new->next = NULL;
		option = new;
	printf(YELLOW"get_lists - option | i = %d\topt = %s\n"RESET, option->i, option->opt); //
	}
	else
	{
		tmp = option;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->i = i;
		new->opt = ft_strdup(opt);
		new->next = NULL;
	printf(YELLOW"get_lists - option | i = %d\topt = %s\n"RESET, new->i, new->opt); //
	}
	return (option);
}

t_args	*fill_args(int i, char *arg, t_args *argmt)
{
	t_args	*tmp;
	t_args	*new;

	if (!(new = (t_args *)malloc(sizeof(*new))))
		ft_exit(RED"error malloc args's list creation"RESET);
	if (argmt == NULL)
	{
		new->i = i;
		new->arg = ft_strdup(arg);
		new->next = NULL;
		argmt = new;
	printf(GREEN"get_lists - args | i = %d\targ = %s\n"RESET, argmt->i, argmt->arg); //
	}
	else
	{
		tmp = argmt;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->i = i;
		new->arg = ft_strdup(arg);
		new->next = NULL;
		printf(GREEN"get_lists - args | i = %d\targ = %s\n"RESET, new->i, new->arg); //
	}
	ft_putstr(RESET); //
	return (argmt);
}
