/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 02:23:09 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_get_lists(int argc, char **argv, t_option **opt, t_args **args)
{
	int			i;

	i = 1;
	if (argv[1][0] == '-')
	{
		while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0' \
				&& (ft_strcmp(argv[i], "--") != 0))
		{
			*opt = fill_option(i, argv[i], *opt);
			i++;
		}
	}
	if (i < argc && ft_strcmp(argv[i], "--") == 0)
		i++;
	while (i < argc)
	{
		*args = fill_args(i, argv[i], *args);
		i++;
	}
	if (args == NULL && *args == NULL)
	{
		*args = fill_args(i, ".", *args);
	}
}

int		main(int argc, char **argv)
{
	t_option	*opt;
	t_args		*args;

	opt = NULL;
	args = NULL;
	if (argc != 1)
		ft_get_lists(argc, argv, &opt, &args);
	if (args == NULL)
		args = fill_args(1, ".", args);
	ft_prog(opt, &args);
	return (0);
}
