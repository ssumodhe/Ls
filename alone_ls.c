/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:00:04 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 17:53:26 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_put_perm_denied(t_args *file)
{
	errno = file->error;
	ft_putstr_fd("ft_ls: ", 2);
	if (ft_strrchr(file->arg, '/') == NULL)
		perror(file->arg);
	else
		perror(ft_strrchr(file->arg, '/') + 1);
}

t_numbers	count_args_2(t_args *file)
{
	t_args		*tmp;
	t_numbers	numbers;

	tmp = file;
	numbers.n_file = 0;
	numbers.n_denied = 0;
	numbers.n_other = 0;
	numbers.removed = 0;
	while (tmp)
	{
		if (S_ISDIR(tmp->stat.st_mode) != 0)
			numbers.n_file++;
		else
			numbers.n_other++;
		tmp = tmp->next;
	}
	return (numbers);
}

void		alone_2(t_args *args, t_flags flag)
{
	t_args	*file;
	t_numbers numbers;

	file = args;
	while (file)
	{
		if (flag.l == 1 && S_ISDIR(file->lstat.st_mode) == 0)
			ft_putendl(file->field);
		else if (flag.l == 0 && S_ISDIR(file->stat.st_mode) == 0)
			ft_putendl(file->arg);
		file = file->next;
	}
	numbers = count_args_2(args);
	if (numbers.n_other != 0 && numbers.n_file >= 1)
		ft_putendl("");
}

void	ft_print_bellow(t_args *file, t_flags flag)
{
	t_args	*tmp;
	char	*split;

	split = NULL;
	tmp = file->bellow;
	if (tmp && flag.l == 1)
	{
		ft_putstr("total ");
		ft_putnbr(tmp->l_total);
		ft_putendl("");
	}
	while (tmp)
	{
		if (flag.l == 1)
			ft_putendl(tmp->field);
		else
		{
			split = (ft_strrchr(tmp->arg, '/') + 1);
			if (split != NULL)
				ft_putendl(split);
			else
				ft_putendl(tmp->arg);
		}
		tmp = tmp->next;
	}
}

void	alone(t_args **args, t_flags flag, t_numbers numbers)
{
	t_args	*tmp;
	int		arguments;

	if (!args)
		return ;
	arguments = 1;
	alone_2(*args, flag);
	tmp = *args;
	while (tmp)
	{
		ft_put_first_list(tmp, numbers, flag);
		if (S_ISDIR(tmp->stat.st_mode) != 0 && arguments < numbers.n_file)
		{
			arguments++;
			ft_putendl("");
		}
		tmp = tmp->next;
	}
}
