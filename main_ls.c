/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:19:29 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/04/21 19:03:17 by ssumodhe         ###   ########.fr       */
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
	while (i < argc)
	{
		if (argv[i][0] == '-') // pour gerer les options.
		{
			if (argv[i][1] && argv[i][1] == '-') // pour le ft_ls --
			{
			// pour le -- , sort quand meme illegal option quand juste --;	
				if (argv[i][2] && argv[i][2] == '\0')
				{
					ft_putstr("hello\n");
				}
				else if (argv[i][2] && argv[i][2] != '\0')
				{
					ft_putstr("ft_ls: illegal option -- ");
					ft_putchar(argv[i][1]);
					ft_exit("\nusage: ft_ls [-lRart] [file ...]");
				}
			}
			j = 1;
			while (argv[i][j] != '\0')
			{
				if (argv[i][j] != 'l' && argv[i][j] != 'R' && argv[i][j] != 'a' \
						&& argv[i][j] != 'r' && argv[i][j] != 't')
				{
					ft_putstr("ft_ls: illegal option -- ");
					ft_putchar(argv[i][j]);
					ft_exit("\nusage: ft_ls [-lRart] [file ...]");
				}
				j++;
			}
		}
		/*
		else pour gerer les arguments.
		*/
		i++;
	}
}
