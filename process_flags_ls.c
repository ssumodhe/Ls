/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:12:08 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/16 20:01:34 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		process_flags(t_args *args, t_flags flag, t_numbers numbers)
{
//	if (flag.none != 1)
//		alone(&args, numbers);
//	if (flag.t == 0 && flag.l_r == 0 && flag.a == 1 && flag.u_r == 0 && flag.l == 0)
//		opt_a(&args, numbers);

		alone(&args, numbers, flag.a);
}
