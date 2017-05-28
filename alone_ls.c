/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:00:04 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/28 20:41:06 by ssumodhe         ###   ########.fr       */
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
	get_error_args(&file->bellow);
	n = ft_strlen(file->arg);
//	ft_putstr(CYAN); //
	while (tmp)
	{
//	printf(YELLOW"ALONE - print_bellow | tmp = %s\terror = %d\n"RESET, tmp->arg, tmp->error); //
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
//	ft_putstr(RESET); //
}
void	alone(t_args **args, t_flags flag, t_numbers numbers)
{
	t_args	*file;
	char	*split;
	int		arguments;

	split = NULL;
	file = *args;
	arguments = 0;

	while (file) //Affiche les fichiers (file->error == 20);
	{
		if (file->error == 20 && flag.u_r != 2)
		{
					//	printf(YELLOW"ALONE | file = %s\terror = %d\n"RESET, file->arg, file->error); //
					//	ft_putstr(RESET); //
			arguments++;
			ft_putendl(file->arg);
			if (arguments == (numbers.n_other - numbers.removed) && (numbers.n_file + numbers.n_denied) != 0)
				ft_putendl("");
		}
		file = file->next;
	}



	file = *args;
	arguments = 0;
	while (file) //Affiche les repositories et les permissions denied "de 1ier ordre"
	{
		if (file->error == 0)
		{
					//	printf(YELLOW"ALONE | file = %s\terror = %d\n"RESET, file->arg, file->error); //
					//	ft_putstr(RESET); //
			arguments++;
			if (file->arg[ft_strlen(file->arg) - 1] != '.' && numbers.n_file + numbers.n_other > 1)
			{
				ft_putstr(file->arg);
				ft_putendl(":");
				ft_print_bellow(file);
				if ((numbers.n_file + numbers.n_other + numbers.n_denied) > 1 && arguments < (numbers.n_file + numbers.n_denied))
					ft_putendl("");
			}
			if (flag.u_r != 0 && file->bellow != NULL)
			{
				flag.u_r = 2;
				alone(&file->bellow, flag, numbers);
			}
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
