/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:02:47 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/02 16:23:37 by ssumodhe         ###   ########.fr       */
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
				ft_putstr_fd("ft_ls: illegal option -- ", 2); //a mettre sur la sortie d'erreur
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

void		ft_free_the_removed(t_args **tmp_removed)
{
	ft_strdel(&(*tmp_removed)->arg);
	ft_strdel(&(*tmp_removed)->field);
	free((*tmp_removed));
}

int			remove_error_args(t_args **args, int removed)
{
	t_args	*tmp;
	t_args	*free; //

	tmp = *args;
	if (tmp != NULL && tmp->error != 0 && tmp->error != 20)
	{
	//	if (tmp->error == 13 && S_ISDIR(tmp->stat.st_mode) == 0)
		if ((tmp->error == 13 && S_ISDIR(tmp->stat.st_mode) == 0) || (tmp->error != 13))
		{
			free = tmp; //
			tmp = tmp->next;
			ft_free_the_removed(&free); //
			*args = tmp;
			removed = remove_error_args(args, removed);
			removed++;
		}
	/*	else if (tmp->error != 13)
		{
			tmp = tmp->next;
			*args = tmp;
			removed = remove_error_args(args, removed);
			removed++;
		}*/
	}
	while (tmp)
	{
		if (tmp->next != NULL && tmp->next->error != 0 && tmp->next->error != 20)
		{
		//	if (tmp->next->error == 13 && S_ISDIR(tmp->next->stat.st_mode) == 0)
			if ((tmp->next->error == 13 && S_ISDIR(tmp->next->stat.st_mode) == 0) || (tmp->next->error != 13))
			{
				free = tmp->next; //
				tmp->next = tmp->next->next;
				ft_free_the_removed(&free); //
				removed = remove_error_args(args, removed);
				removed++;
			}
		/*	else if (tmp->next->error != 13)
			{
				tmp->next = tmp->next->next;
				removed = remove_error_args(args, removed);
				removed++;
			}*/
		}
		tmp = tmp->next;
	}
	return (removed);
}

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

void		ft_prog(t_option *opt, t_args *args)
{
	t_flags		flag;
	int			removed;
	t_numbers	numbers;

	flag = init_flag();
	flag = check_opt(opt, flag);
	args = ft_mergesort(args, ft_ascii_mergesort);
	get_error_args(&args); // recupere les valeurs errno
	put_error_args(&args);
	removed = remove_error_args(&args, 0);
	numbers = get_numbers(args, flag);
	numbers.removed = removed;

	if (flag.u_r == 1) // if -R.
	{
		process_args(&args, flag.a); // creer tous les bellow des args et trie ascii
		process_flags(args, flag); // tri -t et -r et -l
		alone_2(args, flag); // affiche les file NON OUVRABLES
		if (args)
		{
			opt_u_r(&args, flag, numbers);
		}
	}
	else if (flag.u_r == 0) // if pas -R.
	{
		if (flag.t == 1 && args)
			all_args_opt_t(&args);
		if (flag.l_r == 1 && args)
			all_args_opt_r(&args);
		process_args(&args, flag.a);
		process_flags(args, flag);

		alone(&args, flag, numbers);
	}
}
