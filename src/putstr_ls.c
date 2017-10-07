/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 01:16:40 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/14 01:16:41 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		ft_putstr_ls(t_fi *fi)
{
	if (fi->droit[0] == '-')
	{
		if (ft_strstr(fi->droit, "x"))
			ft_putstr_color(fi->name, 31);
		else
			ft_putstr_color(fi->name, 10);
	}
	else if (fi->droit[0] == 'd')
		ft_putstr_color(fi->name, 34);
	else if (fi->droit[0] == 'c')
		ft_putstr_color(fi->name, 101);
	else if (fi->droit[0] == 's')
		ft_putstr_color(fi->name, 10);
	else if (fi->droit[0] == 'l')
		ft_putstr_color(fi->name, 35);
	else if (fi->droit[0] == 'b')
		ft_putstr_color(fi->name, 104);
	else if (fi->droit[0] == 'p')
		ft_putstr_color(fi->name, 10);
}
