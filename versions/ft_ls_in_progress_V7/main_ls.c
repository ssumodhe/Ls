/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/06 18:06:15 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	int			i;
	t_option	*opt;
	t_args		*args;

	opt = NULL;
	args = NULL;
	if (argc != 1)
	{
		i = 1;
		if (ft_strcmp(argv[1], "--") != 0)
		{
			if (argv[1][0] == '-') // pour recuperer les options
			{
				while (i < argc && argv[i][0] == '-' && argv[i][1] != '\0')
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
	}
	if (args == NULL)
		args = fill_args(i, ".", args);
	ft_prog(opt, &args);
//	while(1);
	return (0);
}
