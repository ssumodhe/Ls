/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:14:42 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/04/27 18:10:01 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int argc, char **argv)
{
	DIR		*dir;
	struct dirent *d;

	if (argc == 1)
	{
		ft_exit(RED"Missing arguments"RESET);
	}
	
	if (!(dir = opendir(argv[1])))
	{
		ft_exit(RED"Can't open file"RESET);
	}

	if (!(d = readdir(dir)))
	{
		ft_exit(RED"Can't read file"RESET);
	}

	printf("fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n", d->d_fileno, d->d_reclen, d->d_type, d->d_namlen, d->d_name);
	
	if (closedir(dir) == -1)
	{
		ft_exit("We seem to reach a probleme when closing the directory");
	}
	
	return (0);
}
