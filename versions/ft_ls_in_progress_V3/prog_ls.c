/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:02:47 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/25 16:01:17 by ssumodhe         ###   ########.fr       */
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
	if (flag.t == 1 || flag.l_r == 1 || flag.a == 1 || flag.u_r == 1 || flag.l == 1)
		flag.none = 1;
	return (flag);
}

t_flags		check_opt(t_option *opt, t_flags flag) //fonction qui verifie les options
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
				ft_putstr("ft_ls: illegal option -- "); //a mettre sur la sortie d'erreur
				ft_putchar(tmp->opt[i]);
				ft_exit("\nusage: ft_ls [-lRart] [file ...]");
			}
			else
				flag = fill_flag(flag, tmp->opt[i]);
			i++;
		}
		tmp = tmp->next;
	}
	return (flag);
}
/*
void		ascii_order_args(t_args **args)
{
	t_args	*current;
	t_args	*after;
	char	*tmp;
	int		i;

	current = *args;
	after = current->next;
	while (current && after)
	{
		i = 0;
		while (current->arg[i] == after->arg[i])
			i++;
		if (current->arg[i] > after->arg[i])
		{
			tmp = ft_strdup(current->arg);
			ft_strdel(&current->arg);
			current->arg = ft_strdup(after->arg);
			ft_strdel(&after->arg);
			after->arg = ft_strdup(tmp);
			ft_strdel(&tmp);
			ascii_order_args(args);
		}
		current = current->next;
		after = after->next;
	}
}
*/
void		get_error_args(t_args **args)
{
	DIR		*dir;
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		errno = 0;
		dir = opendir(tmp->arg);
		tmp->error = errno;
//		printf("args = %s\terror = %d\n", tmp->arg, tmp->error);
		if (dir != NULL)
			if (closedir(dir) == -1)
				ft_exit("We seem to reach a problem when closing the directory");
		tmp = tmp->next;
	}
}

void		put_error_args(t_args **args)
{
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		if (tmp->error != 0 && tmp->error != 13 && tmp->error != 20)
		{
			errno = tmp->error;
			ft_putstr_fd("ft_ls: ", 2);
			perror(tmp->arg);
		}
		tmp = tmp->next;
	}
}

int			remove_error_args(t_args **args, int removed)
{
	t_args	*tmp;

	tmp = *args;
	if (tmp && tmp->error != 0 && tmp->error != 13 && tmp->error != 20)
	{
		removed++;
		tmp = tmp->next;
		*args = tmp;
		removed = remove_error_args(args, removed);
	}
	while (tmp)
	{
		if (tmp->next != NULL && tmp->next->error != 0 && tmp->next->error != 13 && tmp->next->error != 20)
		{
			removed++;
			tmp->next = tmp->next->next;
			removed = remove_error_args(args, removed);
		}
		tmp = tmp->next;
	}
	return (removed);
}

t_numbers	count_args(t_args **args)
{
	t_args		*tmp;
	t_numbers	numbers;

	tmp = *args;
	numbers.n_file = 0;
	numbers.n_denied = 0;
	numbers.n_other = 0;
	while (tmp)
	{
		if (tmp->error == 0)
			numbers.n_file++;
		else if (tmp->error == 13)
			numbers.n_denied++;
		else
			numbers.n_other++;
		tmp = tmp->next;
	}
	return (numbers);
}

void		ft_prog(t_option *opt, t_args *args)
{
	t_flags		flag;
	t_numbers	numbers;

	flag = init_flag();
	flag = check_opt(opt, flag);
	printf(CYAN"prog - flags | l = %d\tR = %d\ta = %d\tr = %d\tt = %d\n"RESET, flag.l, flag.u_r, flag.a, flag.l_r, flag.t); //
	ft_putstr(RESET); //
//	ascii_order_args(&args);
	args = ft_mergesort(args, ft_ascii_mergesort);
	get_error_args(&args);
	put_error_args(&args);
	numbers = count_args(&args);
	numbers.removed = remove_error_args(&args, 0);
	process_args(&args);
//	process_args(&args, flag.a);
//	printf("n_file = %d\tn_other = %d, removed = %d\n", numbers.n_file, numbers.n_other, numbers.removed);
	process_flags(args, flag, numbers);
}
