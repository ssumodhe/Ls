/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/04/24 18:17:56 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	int			i;
	t_option	*opt;
	t_args		*args;
//	t_option	*tmp_o;
//	t_args		*tmp_a;

/*
** - attention au ls tout seul
** - attention au ls --
*/

	opt = NULL;
	args = NULL;
	i = 1;
	if (argv[1][0] == '-') // pour recuperer les options
	{
		while (i < argc && argv[i][0] == '-')
		{
			opt = fill_option(i, argv[i], opt);
			i++;
		}
	}
	while (i < argc) // pour recuperer les arguments
	{
		args = fill_args(i, argv[i], args);
		i++;
	}

/* // print les listes
	tmp_o = opt;
	while (tmp_o != NULL)
	{
		printf(BLUE"main - option | i = %d\topt = %s\n"RESET, tmp_o->i, tmp_o->opt);
		tmp_o = tmp_o->next;
	}
	tmp_a = args;
	while (tmp_a != NULL)
	{
		printf(BLUE"main - args | i = %d\targ = %s\n"RESET, tmp_a->i, tmp_a->arg);
		tmp_a = tmp_a->next;
	}
*/

	ft_prog(opt, args);

	return (0);
}
