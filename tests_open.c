/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:14:42 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/04/29 23:20:24 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	DIR		*dir;
	DIR		*dir_2;
	struct dirent *d;
	struct dirent *d_2;

	if (argc == 1)
	{
		ft_exit(RED"Missing arguments"RESET);
	}

	if (!(dir = opendir(argv[1])))
	{
		ft_exit(RED"Can't open file"RESET);
	}


	while ((d = readdir(dir)))
	{
		printf("fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n", d->d_fileno, d->d_reclen, d->d_type, d->d_namlen, d->d_name);
		if (d->d_type == 4 && d->d_name[0] != '.')
		{
			errno = 0;
			if (!(dir_2 = opendir(d->d_name)))
			{
				printf("errno is %d\n", errno);
				ft_exit(RED"Can't open file"RESET);
			}
			while ((d_2 = readdir(dir_2)))
			{
				printf(YELLOW"fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n"RESET, d_2->d_fileno, d_2->d_reclen, d_2->d_type, d_2->d_namlen, d_2->d_name);

			}
			if (closedir(dir_2) == -1)
			{
				ft_exit("We seem to reach a probleme when closing the directory");
			}
		}
	}


	if (closedir(dir) == -1)
	{
		ft_exit("We seem to reach a probleme when closing the directory");
	}

	return (0);
}
