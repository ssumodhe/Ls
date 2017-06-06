/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:14:40 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 00:18:11 by ssumodhe         ###   ########.fr       */
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
//	printf(YELLOW"get_lists - option | i = %d\topt = %s\n"RESET, option->i, option->opt); //
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
//	printf(YELLOW"get_lists - option | i = %d\topt = %s\n"RESET, new->i, new->opt); //
	}
	return (option);
}

t_args	*new_args(int i, char *arg)
{
	t_args	*new;

	if (!(new = (t_args *)malloc(sizeof(*new))))
		ft_exit(RED"error malloc args's list creation"RESET);
	new->i = i;
	new->arg = ft_strdup(arg);
	new->field = NULL;
	new->error = 0;
	new->d_type = 0; // a virer??
	get_stat(new);
	get_link_stat(new);
	new->l_total = 0;
	new->bellow = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_args	*fill_args(int i, char *arg, t_args *argmt)
{
	t_args	*tmp;

	if (argmt == NULL)
	{
		argmt = new_args(i, arg);
//		printf(GREEN"get_lists - args | i = %d\targ = %s\n"RESET, argmt->i, argmt->arg); //
	}
	else
	{
		tmp = argmt;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_args(i, arg);
//		printf(GREEN"get_lists - args | i = %d\targ = %s\n"RESET, tmp->next->i, tmp->next->arg); //
	}
	return (argmt);
}
/*
void	ft_get_lists(int argc, char **argv, t_option **opt, t_args **args)
{
	int			i;

	i = 1;
	if (argv[1][0] == '-') // pour recuperer les options
	{
		while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
		{
			*opt = fill_option(i, argv[i], *opt);
			i++;
		}
	}
	while (i < argc) // pour recuperer les arguments
	{
		*args = fill_args(i, argv[i], *args);
		i++;
	}
	if (*args == NULL)
		*args = fill_args(i, ".", *args);
}*/
