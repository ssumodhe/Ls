/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 15:48:18 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
