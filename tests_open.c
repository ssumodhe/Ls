/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:14:42 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/05/01 17:46:02 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_strjoin_path(char *str1, char c, char *str2)
{
	int		n1;
	int		n2;
	int		a;
	int		b;
	char	*join;

	if (str1 == NULL || str2 == NULL)
		return (NULL);
	n1 = ft_strlen(str1);
	n2 = ft_strlen(str2);
	if (!(join = (char *)malloc(sizeof(char) * (n1 + n2 + 2))))
		return (NULL);
	join[n1 + n2 + 1] = '\0';
	a = 0;
	while (str1[a] != '\0')
	{
		join[a] = str1[a];
		a++;
	}
	join[a++] = c;
	b = 0;
	while (str2[b] != '\0')
		join[a++] = str2[b++];
	return(join);
}


void	ft_openfiles(char *str)
{
	DIR		*dir;
//	DIR		*dir_2;
	struct dirent *d;
//	struct dirent *d_2;
	static int	cpt = 0;
	char	*both;


	if (!(dir = opendir(str)))
	{
		ft_exit(RED"Can't open file"RESET);
	}


	while ((d = readdir(dir)))
	{
		if (cpt == 0)
			printf(CYAN"fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n", d->d_fileno, d->d_reclen, d->d_type, d->d_namlen, d->d_name);
		if (cpt == 1)
			printf(RED"fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n", d->d_fileno, d->d_reclen, d->d_type, d->d_namlen, d->d_name);
		if (cpt == 2)
			printf(GREEN"fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n", d->d_fileno, d->d_reclen, d->d_type, d->d_namlen, d->d_name);
		if (cpt > 2)
			printf(BLUE"fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n", d->d_fileno, d->d_reclen, d->d_type, d->d_namlen, d->d_name);
		if (d->d_name[0] != '.' && d->d_type == 4)
		{
			errno = 0;
			printf(YELLOW"name is %s\n", d->d_name);
			cpt++;
			both = ft_strjoin_path(str, '/' ,d->d_name);
			ft_openfiles(d->d_name);

		/*
			if ((dir_2 = opendir(d->d_name)))
			{
				printf(YELLOW"open errno is %d\n", errno);
				printf("name is %s\n", d->d_name);
				while ((d_2 = readdir(dir_2)))
				{
					printf(YELLOW"fileno = %llu, reclen = %d, type = %hhu, namelen = %hu, name = %s\n"RESET, d_2->d_fileno, d_2->d_reclen, d_2->d_type, d_2->d_namlen, d_2->d_name);

				}
				if (closedir(dir_2) == -1)
				{
					printf("close errno is %d\n", errno);
					ft_exit("We seem to reach a probleme when closing the directory");
				}

			}*/
		}
	}


	if (closedir(dir) == -1)
	{
		ft_exit("We seem to reach a probleme when closing the directory");
	}

}



int		main(int argc, char **argv)
{
	char	*join;

	if (argc == 1)
	{
		ft_exit(RED"Missing arguments"RESET);
	}

	join = ft_strjoin_path(argv[1], '/', argv[2]);
	printf("join is \"%s\"\n", join);

//	ft_openfiles(argv[1]);

	return (0);
}
