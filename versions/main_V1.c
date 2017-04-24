/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/04/24 20:01:40 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	int		i;
	int		j;

	/*
	** Check les illegal option
	*/

	i = 1;
	ill_opt = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-') // pour gerer les options.
		{
			if (argv[i][1] && argv[i][1] == '-') // pour le ft_ls --
			{
				if (argv[i][2] == '\0')
				{
					ft_putstr("Je rentre dans la fonction qui gere le ft_ls --\n");
				}
				else if (argv[i][2] != '\0')
				{
					ft_putstr("ft_ls: illegal option -- ");
					ft_putchar(argv[i][1]);
					ft_exit("\nusage: ft_ls [-lRart] [file ...]");
				}
			}
			else
			{
				j = 1;
				while (argv[i][j] != '\0') // pour les -lRart
				{
					if (argv[i][j] != 'l' && argv[i][j] != 'R' && argv[i][j] != 'a' \
							&& argv[i][j] != 'r' && argv[i][j] != 't')
					{
						ft_putstr("ft_ls: illegal option -- ");
						ft_putchar(argv[i][j]);
						ft_exit("\nusage: ft_ls [-lRart] [file ...]");
					}
					else
					{
						ft_putstr("Je rentre dans la fonction qui gere le ft_ls -");
						ft_putchar(argv[i][j]);
						ft_putchar('\n');
					}
					j++;
				}
			}
		}
		/*
		else pour gerer les arguments.
		*/
		i++;
	}
}
