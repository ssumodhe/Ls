/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:02:47 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/04/24 20:01:37 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		check_opt(t_option *opt)
{
	int			i;
	t_option	tmp;
	t_flags		flag;

	tmp = opt;
	while (opt != NULL)
	{
		i = 1;
		while (opt->opt[i] != '\0')
		{
			if(opt->opt[i] != 'l' && opt->opt[i] != 'R' && opt->opt[i] != 'a' \
					opt->opt[i] != 'r' && opt->opt[i] != 't')
			{
				ft_putstr("ft_ls: illegal option -- ");
				ft_putchar(opt->opt[i]);
				ft_exit("\nusage: ft_ls [-lRart] [file ...]");
			}
			//else remplir la structure puis return la strucutre flag
			i++;
		}
		opt = opt->next;
	}

}

void		ft_prog(t_option *opt, t_args *args)
{
	
	flags = check_opt(opt);
	args = check_args(args);
}
