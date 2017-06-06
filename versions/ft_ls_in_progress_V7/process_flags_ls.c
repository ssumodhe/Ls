/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:12:08 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/06 18:06:18 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		process_flags(t_args **args, t_flags flag)
{
	if (flag.t == 1 && args && *args)
	{
			all_args_opt_t(args);
//		if (flag.u_r == 0)
//			all_args_opt_t(&args);
	//	opt_t(&args); //pour les bellow
	}

	if (flag.l_r == 1 && args && *args)
	{
			all_args_opt_r(args);
//		if (flag.u_r == 0)
//			all_args_opt_r(&args);
//		opt_l_r(&args); //pour les bellow
	}

	if (flag.l == 1 && args && *args)
	{
		(*args)->l_total = all_args_opt_l(*args);
/*		ft_putstr(PURPLE HIGHLIGHT"l_total ");
		ft_putnbr((*args)->l_total);
		ft_putstr("  de  ");
		ft_putstr((*args)->arg);
		ft_putendl(""RESET);*/
		//opt_l(args);
	}

}
