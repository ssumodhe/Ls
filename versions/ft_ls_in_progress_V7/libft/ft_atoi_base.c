/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 13:34:49 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/03/30 16:51:47 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getresult(char c, int base, int j)
{
	if (c >= '0' && c <= '9')
		j = (j * base) + (c - '0');
	else if (base > 10 && c >= 'a' && c <= 'z')
		j = (j * base) + (c - 'a') + 10;
	else if (base > 10 && c >= 'A' && c <= 'Z')
		j = (j * base) + (c - 'A') + 10;
	return (j);
}

int		ft_atoi_base(const char *str, int str_base)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 1;
	if (str_base > 16 || str_base < 2)
		return (0);
	while (str[i] != '\0' && ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		k = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		j = ft_getresult(str[i], str_base, j);
		i++;
	}
	return (j * k);
}
