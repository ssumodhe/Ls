/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:12:08 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/08 00:54:41 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		process_flags(t_args **args, t_flags flag)
{
	if (flag.t == 1 && args && *args)
	{
		all_args_opt_t(args);
	}
	if (flag.l_r == 1 && args && *args)
	{
		all_args_opt_r(args);
	}
	if (flag.l == 1 && args && *args)
	{
		(*args)->l_total = all_args_opt_l(*args);
	}
}
