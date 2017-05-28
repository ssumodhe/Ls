/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:00:04 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/27 22:22:24 by ssumodhe         ###   ########.fr       */
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

void	ft_print_bellow(t_args *file)
{
	t_args	*tmp;
	char 	*split;
	int		n;

	split = NULL;
	tmp = file->bellow;
	n = ft_strlen(file->arg);
	get_error_args(&file->bellow);
	while (tmp)
	{
//	printf(YELLOW"ALONE - print_bellow | tmp = %s\terror = %d\n"RESET, tmp->arg, tmp->error); //
//	ft_putstr(RESET); //
		split = ft_strwithoutstart(tmp->arg, (n + 1));
		if (tmp->error == 13)
		{	
			errno = tmp->error;
			ft_putstr_fd("ft_ls: ", 2);
			perror(split);
		}
		else
			ft_putendl(split);
		ft_strdel(&split);
		tmp = tmp->next;
	}
}
void	alone(t_args **args, t_numbers numbers)
{
	t_args	*file;
	char	*split;
	int		arguments;

	split = NULL;
	file = *args;
	arguments = 0;
	



	while (file) //Affiche les fichiers (file->error == 20);
	{
		if (file->error == 20/* || file->error == 13*/)
		{
//	printf(YELLOW"ALONE | file = %s\terror = %d\n"RESET, file->arg, file->error); //
//	ft_putstr(RESET); //
			arguments++;
/*			if (file->error == 13)
			{	
				errno = file->error;
				ft_putstr_fd("ft_ls: ", 2);
				perror(file->arg);
			}
			else*/
				ft_putendl(file->arg);
			if (arguments == (numbers.n_other - numbers.removed) && (numbers.n_file + numbers.n_denied) != 0)
				ft_putendl("");
		}
/*		else if (file->error == 13)
			{	
			arguments++;
				errno = file->error;
				ft_putstr_fd("ft_ls: ", 2);
				perror(file->arg);
			if (arguments == (numbers.n_other - numbers.removed) && (numbers.n_file + numbers.n_denied) != 0)
				ft_putendl("");
			}*/

		file = file->next;
	}
	file = *args;
	arguments = 0;
	while (file) //Affiche les 
	{
		if (file->error == 0)
		{
//	printf(YELLOW"ALONE | file = %s\terror = %d\n"RESET, file->arg, file->error); //
//	ft_putstr(RESET); //
			arguments++;
			if (numbers.n_file + numbers.n_other > 1)
			{
				ft_putstr(file->arg);
				ft_putendl(":");
			}
			ft_print_bellow(file);
			if ((numbers.n_file + numbers.n_other + numbers.n_denied) > 1 && arguments < (numbers.n_file + numbers.n_denied))
				ft_putendl("");
		}
		else if (file->error == 13)
		{	
//	printf(YELLOW"ALONE | file = %s\terror = %d\n"RESET, file->arg, file->error); //
//	ft_putstr(RESET); //
			arguments++;
			ft_putstr_fd(file->arg, 2);
			ft_putendl_fd(":", 2);
			errno = file->error;
			ft_putstr_fd("ft_ls: ", 2);
			if (ft_strrchr(file->arg, '/') == NULL)
				perror(file->arg);
			else
				perror(ft_strrchr(file->arg, '/') + 1);
		if ((numbers.n_file + numbers.n_other + numbers.n_denied) > 1 && arguments < (numbers.n_file + numbers.n_denied))
			ft_putendl("");
		}
		file = file->next;
	}
}
