/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:02:47 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/01 17:27:40 by ssumodhe         ###   ########.fr       */
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
	while (tmp != NULL)
	{
		i = 1;
		while (tmp->opt[i] != '\0')
		{
			if (tmp->opt[i] != 'l' && tmp->opt[i] != 'R' && tmp->opt[i] != 'a' \
					&& tmp->opt[i] != 'r' && tmp->opt[i] != 't')
			{
				ft_putstr("ft_ls: illegal option -- ");
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

void		check_args(t_args **args)
{
	DIR		*dir;
	t_args	*tmp;

	tmp = *args;
	while (tmp)
	{
		errno = 0;
		if ((!(dir = opendir(tmp->arg))))
		{
			tmp->error = errno;
			if (errno == 2)
			{
				ft_putstr(RESET); //
				ft_putstr("ft_ls: ");
				ft_putstr(tmp->arg);
				ft_putendl(": No such file or directory");
			}
		}
		else
		{
			ft_putstr(GREEN"prog_ls - check_args: "); //
			ft_putstr("OK: "); //
			ft_putendl(tmp->arg); //
			ft_putstr(RESET); //
			tmp->error = errno;
			if (closedir(dir) == -1)
				ft_exit("We seem to reach a problem when closing the directory");
		}
		tmp = tmp->next;
	}
}
/*
   void		remove_error_args(t_args **args)
   {
   t_args	*tmp;
   t_args	*prev;

   prev = *args;
   while (prev && prev->error == 2)
   {
   prev = prev->next;
   }
 *args = prev;
 tmp = prev->next;
 while (prev && tmp)
 {
 if (tmp->error == 2)
 {
 printf("args : %s\n", tmp->arg);
//	tmp = tmp->next;
//prev = tmp;
//tmp = tmp->next;
prev->next = tmp->next;
tmp = tmp->next;
}
else 
prev = prev->next;
tmp = tmp->next;
}
}
*/



void		remove_error_args(t_args **args)
{
	t_args 		*tmp;
	t_args 		*prev;

	tmp = *args;
	if (tmp && tmp->error == 2)
	{
		tmp = tmp->next;
		*args = tmp;
		remove_error_args(args);
	}
	while (tmp)
	{
		if (tmp->next && tmp->next->error == 2)
			tmp->next = tmp->next->next;
		prev = tmp;
		tmp = tmp->next;
		if (tmp && tmp->error == 2)
			prev->next = tmp->next;
	}
}

void		ft_prog(t_option *opt, t_args *args)
{
	t_flags		flag;
	t_args		*tmp;

	flag = init_flag();
	flag = check_opt(opt, flag);
	printf(CYAN"prog_ls - flag | l = %d\tR = %d\ta = %d\tr = %d\tt = %d\n"RESET, flag.l, flag.u_r, flag.a, flag.l_r, flag.t); //


	if (args != NULL)
	{
		ascii_order_args(&args);

		tmp = args;
		while (tmp != NULL)
		{
			printf(CYAN"prog_ls - ascii | arg = %s\n"RESET, tmp->arg ); //
			tmp = tmp->next;
		}


		check_args(&args);

		tmp = args;
		while (tmp != NULL)
		{
			printf(CYAN"prog_ls - args + errno | arg = %s, errno = %d\n"RESET, tmp->arg, tmp->error); //
			tmp = tmp->next;
		}

		remove_error_args(&args);
		tmp = args;
		while (tmp != NULL)
		{
			printf(YELLOW"prog_ls - args - errno==2 | arg = %s, errno = %d\n"RESET, tmp->arg, tmp->error); //
			tmp = tmp->next;
		}
	}

}



















