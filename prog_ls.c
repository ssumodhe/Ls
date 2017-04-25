/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:02:47 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/04/25 19:47:27 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags		init_flag(void)
{
	t_flags		flag;

	flag.l = 0;
	flag.u_r = 0;
	flag.a = 0;
	flag.l_r = 0;
	flag.t = 0;
	return (flag);
}

t_flags		fill_flag(t_flags flag, char c)
{
	if (c == 'l')
		flag.l = 1;
	else if (c == 'R')
		flag.u_r = 1;
	else if (c == 'a')
		flag.a = 1;
	else if (c == 'r')
		flag.l_r = 1;
	else if (c == 't')
		flag.t = 1;
	return (flag);
}

t_flags		check_opt(t_option *opt, t_flags flag) //fonction qui verifie les options
{
	int			i;
	t_option	*tmp;

	tmp = opt;
	while (opt != NULL)
	{
		i = 1;
		while (opt->opt[i] != '\0')
		{
			if (opt->opt[i] != 'l' && opt->opt[i] != 'R' && opt->opt[i] != 'a' \
					&& opt->opt[i] != 'r' && opt->opt[i] != 't')
			{
				ft_putstr("ft_ls: illegal option -- ");
				ft_putchar(opt->opt[i]);
				ft_exit("\nusage: ft_ls [-lRart] [file ...]");
			}
			else
				flag = fill_flag(flag, opt->opt[i]);
			i++;
		}
		opt = opt->next;
	}
	return (flag);
}

void		ft_prog(t_option *opt, t_args *args)
{
	t_flags		flag;
	(void)args;	

	flag = init_flag();
	flag = check_opt(opt, flag);
	printf(CYAN"prog_ls - flag | l = %d\tR = %d\ta = %d\tr = %d\tt = %d\n"RESET, flag.l, flag.u_r, flag.a, flag.l_r, flag.t); //
//	args = check_args(args);
}
