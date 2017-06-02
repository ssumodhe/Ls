/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/02 14:59:06 by ssumodhe         ###   ########.fr       */
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

	opt = NULL;
	args = NULL;
	if (argc != 1)
	{
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
		
	}
	if (args == NULL)
		args = fill_args(i, ".", args);

/* // print les listes
	tmp_o = opt;
	while (tmp_o != NULL)
	{
		printf(BLUE"Main - option | i = %d\topt = %s\n"RESET, tmp_o->i, tmp_o->opt);
		tmp_o = tmp_o->next;
	}
	tmp_a = args;
	while (tmp_a != NULL)
	{
		printf(BLUE"Main - args | i = %d\targ = %s\n"RESET, tmp_a->i, tmp_a->arg);
		tmp_a = tmp_a->next;
	}
*/


//	printf("Main | opt = %d\n", opt->i);
//	printf("Main | args = %d\n", args->i);
	
//	all_args_opt_t(&args);
//	all_args_opt_r(&args);
	ft_prog(opt, args);

	return (0);
}
