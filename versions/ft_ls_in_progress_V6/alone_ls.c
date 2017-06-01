/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alone_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:00:04 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/31 20:27:48 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
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
*/
void	ft_print_bellow(t_args *file)
{
	t_args	*tmp;
	char 	*split;

	split = NULL;
	tmp = file->bellow;
	while (tmp)
	{
		split = (ft_strrchr(tmp->arg, '/') + 1);
		if (split != NULL)
			ft_putendl(split);
		else
			ft_putendl(tmp->arg); // Mis en protection
		tmp = tmp->next;
	}
}



void	alone(t_args **args, t_flags flag, t_numbers numbers)
{
	t_args	*file;
	char	*split;
	int		arguments;
	(void)flag;

	split = NULL;
	file = *args;
	arguments = 0;

	while (file) //Affiche les fichiers (file->error == 20);
	{
		if (file->error == 20)
		{
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
			arguments++;
			if ((check_if_point(file->arg) == 0) && numbers.n_file + numbers.n_other > 1)
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
			arguments++;
		/*	ft_putstr_fd(file->arg, 2);
			ft_putendl_fd(":", 2);
			errno = file->error;
			ft_putstr_fd("ft_ls: ", 2);
			if (ft_strrchr(file->arg, '/') == NULL)
				perror(file->arg);
			else
				perror(ft_strrchr(file->arg, '/') + 1);*/
			ft_putstr(file->arg);
			ft_putendl(":");
			ft_put_perm_denied(file); /// condition a mettre pour savoir si nom du dossier ou pas ! 
		if ((numbers.n_file + numbers.n_other + numbers.n_denied) > 1 && arguments < (numbers.n_file + numbers.n_denied))
			ft_putendl("");
		}
		file = file->next;
	}
}
