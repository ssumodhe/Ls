/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_flags_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 18:12:08 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/30 15:42:05 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		process_flags(t_args *args, t_flags flag)
{
//	t_args	*tmp; //
//	int			i; //

	if (flag.t == 1)
	{
	//	all_args_opt_t(&args);
		opt_t(&args); // pour -R
	}

	if (flag.l_r == 1)
	{
	//	all_args_opt_r(&args);
		opt_l_r(&args); // pour -R
	}

/*
// tests.
	printf(BLUE"process_flags | numbers file : %d, denied : %d, other : %d\n"RESET, numbers.n_file, numbers.n_denied, numbers.n_other);
	printf(BLUE"process_flags | numbers total args = %d\n"RESET, numbers.n_file + numbers.n_denied + numbers.n_other);

	tmp = args;
	i = 1;
	while (tmp)
	{
		printf(BLUE"process_flags | %d) i = %d name = %s\n"RESET, i, tmp->i, tmp->arg);
		tmp = tmp->next;
		i++;
	}
	ft_putstr(RESET); //
//end-tests.*/

}
