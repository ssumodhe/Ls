/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:00:04 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/18 14:30:38 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strwithoutstart(char *str, int size)
{
	char	*split;
	int		i;

	i = ft_strlen(str);
	if (!(split = (char *)malloc(sizeof(char) * (i - size))))
		ft_exit(RED"error malloc spliting args' name"RESET);
	i = 0;
	while (str[size] != '\0')
	{
		split[i] = str[size];
		i++;
		size++;
	}
	split[i] = '\0';
	return (split);
}

void	ft_print_bellow(t_args *file, int opt_a)
{
	t_args	*tmp;
	char 	*split;
	int		n;

	split = NULL;
	tmp = file->bellow;
	n = ft_strlen(file->arg);
	if (opt_a == 0)
	{
		while (tmp)
		{
			if (tmp->arg[n + 1] != '.')
			{
				split = ft_strwithoutstart(tmp->arg, (n + 1));
				ft_putendl(split);
				ft_strdel(&split);
			}
			tmp = tmp->next;
		}
	}
	else
		while (tmp)
		{
			split = ft_strwithoutstart(tmp->arg, (n + 1));
			ft_putendl(split);
			ft_strdel(&split);
			tmp = tmp->next;
		}
}

void	alone(t_args **args, t_numbers numbers, int opt_a)
{
	t_args	*file;
	int		arguments;

	file = *args;
	arguments = 0;
	while (file)
	{
		if (file->error != 0)
		{
			arguments++;
			ft_putendl(file->arg);
			if (file->error == 13)
			if (arguments == (numbers.n_other - numbers.removed) && numbers.n_file != 0)
				ft_putendl("");
		}
		file = file->next;
	}
	file = *args;
	arguments = 0;
	while (file)
	{
		if (file->error == 0)
		{
			arguments++;
			if (numbers.n_file + numbers.n_other > 1)
			{
				ft_putstr(file->arg);
				ft_putendl(":");
			}
			ft_print_bellow(file, opt_a);
			if (numbers.n_file + numbers.n_other > 1 && arguments < numbers.n_file)
				ft_putendl("");
		}
		file = file->next;
	}
}
