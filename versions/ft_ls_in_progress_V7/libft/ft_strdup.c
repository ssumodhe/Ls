/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 13:30:13 by ssumodhe          #+#    #+#             */
/*   Updated: 2016/11/25 17:08:45 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*cpy;
	int		n;

	n = 0;
	while (src[n] != '\0')
		n++;
	if ((cpy = (char *)malloc(sizeof(char) * (n + 1))) == NULL)
		return (NULL);
	n = 0;
	while (src[n] != '\0')
	{
		cpy[n] = src[n];
		n++;
	}
	cpy[n] = '\0';
	return (cpy);
}
