/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:02:47 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/08 00:54:34 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_error_args(t_args **args)
{
	DIR		*dir;
	t_args	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		errno = 0;
		dir = opendir(tmp->arg);
		tmp->error = errno;
		if (dir != NULL)
			if (closedir(dir) == -1)
				ft_exit(PB_CLOSE_DIR);
		tmp = tmp->next;
	}
}

void		put_error_args(t_args **args)
{
	t_args	*tmp;

	if (!args)
		return ;
	tmp = *args;
	while (tmp)
	{
		if (tmp->error != 0 && tmp->error != 20)
		{
			if (tmp->error == 13 && S_ISDIR(tmp->stat.st_mode) == 0)
			{
				errno = tmp->error;
				ft_putstr_fd("ft_ls: ", 2);
				perror(tmp->arg);
			}
			else if (tmp->error != 13)
			{
				errno = tmp->error;
				ft_putstr_fd("ft_ls: ", 2);
				perror(tmp->arg);
			}
		}
		tmp = tmp->next;
	}
}

void		ft_if_no_ur(t_args **args, t_flags flag, t_numbers numbers)
{
	process_args(args, flag.a);
	process_flags(args, flag);
	if (flag.t == 1 && *args)
		opt_t(args);
	if (flag.l_r == 1 && *args)
		opt_l_r(args);
	if (flag.l == 1 && *args)
		opt_l(args);
	alone(args, flag, numbers);
}

void		ft_if_upper_r(t_args **args, t_flags flag, t_numbers numbers)
{
	process_args(args, flag.a);
	process_flags(args, flag);
	if (flag.t == 1 && *args)
		opt_t(args);
	if (flag.l_r == 1 && *args)
		opt_l_r(args);
	if (flag.l == 1 && *args)
		opt_l(args);
	alone_2(*args, flag);
	if (*args)
	{
		opt_u_r(args, flag, numbers);
	}
}

void		ft_prog(t_option *opt, t_args **args)
{
	t_flags		flag;
	int			removed;
	t_numbers	numbers;

	if (!args)
		return ;
	flag = init_flag();
	flag = check_opt(opt, flag);
	*args = ft_mergesort(*args, ft_ascii_mergesort);
	get_error_args(args);
	put_error_args(args);
	removed = remove_error_args(args, 0);
	numbers = get_numbers(*args, flag);
	numbers.removed = removed;
	if (flag.u_r == 1)
		ft_if_upper_r(args, flag, numbers);
	else if (flag.u_r == 0)
		ft_if_no_ur(args, flag, numbers);
}
