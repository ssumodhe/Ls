/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_mod_ls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssumodhe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:48:40 by ssumodhe          #+#    #+#             */
/*   Updated: 2017/06/07 16:02:37 by ssumodhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_modif_date_mergesort(t_args **tmp, t_args **left, t_args **right)
{
	if ((*left)->lstat.st_mtimespec.tv_sec >= (*right)->lstat.st_mtimespec.tv_sec)
	{
		*tmp = *left;
		*left = (*left)->next;
	}
	else
	{
		*tmp = *right;
		*right = (*right)->next;
	}
}

void	ft_ascii_mergesort(t_args **tmp, t_args **left, t_args **right)
{
	if ((ft_strcmp((*left)->arg, (*right)->arg)) < 0)
	{
		*tmp = *left;
		*left = (*left)->next;
	}
	else
	{
		*tmp = *right;
		*right = (*right)->next;
	}
}
