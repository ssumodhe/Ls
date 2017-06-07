/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_options_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:24:50 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 15:28:51 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_numbers	get_numbers(t_args *args, t_flags flag)
{
	t_args		*tmp;
	t_numbers	numbers;

	tmp = args;
	numbers.n_file = 0;
	numbers.n_other = 0;
	while (tmp)
	{
		if (flag.l == 1)
		{
			if (S_ISDIR(tmp->lstat.st_mode) != 0)
				numbers.n_file++;
			if (S_ISDIR(tmp->lstat.st_mode) == 0)
				numbers.n_other++;
		}
		else
		{
			if (S_ISDIR(tmp->stat.st_mode) != 0)
				numbers.n_file++;
			if (S_ISDIR(tmp->stat.st_mode) == 0)
				numbers.n_other++;
		}
		tmp = tmp->next;
	}
	return (numbers);
}

t_flags		init_flag(void)
{
	t_flags		flag;

	flag.l = 0;
	flag.u_r = 0;
	flag.a = 0;
	flag.l_r = 0;
	flag.t = 0;
	flag.none = 0;
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
	if (flag.t == 1 || flag.l_r == 1 || flag.a == 1 || flag.u_r == 1 \
			|| flag.l == 1)
		flag.none = 1;
	return (flag);
}

t_flags		check_opt(t_option *opt, t_flags flag)
{
	int			i;
	t_option	*tmp;

	tmp = opt;
	while (tmp != NULL)
	{
		i = 1;
		while (tmp->opt[i] != '\0')
		{
			if (tmp->opt[i] != 'l' && tmp->opt[i] != 'R' && tmp->opt[i] != 'a' \
					&& tmp->opt[i] != 'r' && tmp->opt[i] != 't')
			{
				ft_putstr_fd("ft_ls: illegal option -- ", 2);
				ft_putchar_fd(tmp->opt[i], 2);
				ft_putstr_fd("\nusage: ft_ls [-lRart] [file ...]", 2);
				ft_exit("");
			}
			else
				flag = fill_flag(flag, tmp->opt[i]);
			i++;
		}
		tmp = tmp->next;
	}
	return (flag);
}
