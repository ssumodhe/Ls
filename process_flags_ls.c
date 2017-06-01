/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:12:08 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/01 19:49:02 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		process_flags(t_args *args, t_flags flag)
{
	if (flag.t == 1)
	{
//		if (flag.u_r == 0)
//			all_args_opt_t(&args);
		opt_t(&args); //pour les bellow
	}

	if (flag.l_r == 1)
	{
//		if (flag.u_r == 0)
//			all_args_opt_r(&args);
		opt_l_r(&args); //pour les bellow
	}

//	if (flag.l == 1)
//	{
//		opt_l(args);
//	}

}
