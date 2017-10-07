/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 14:17:00 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 18:56:36 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int			fill_flag(char ***flag)
{
	if ((*flag = malloc(sizeof(char *) * 2)) == NULL)
		return (ft_puterr("Malloc 1 fail in fill_flag\n"));
	if (((*flag)[0] = malloc(sizeof(char) * 8)) == NULL)
		return (ft_puterr("Malloc 2 fail in fill_flag\n"));
	(*flag)[0][0] = 'l';
	(*flag)[0][1] = 'a';
	(*flag)[0][2] = 'r';
	(*flag)[0][3] = 't';
	(*flag)[0][4] = 'R';
	(*flag)[0][5] = '\0';
	(*flag)[0][6] = 0;
	(*flag)[0][7] = 0;
	if (((*flag)[1] = malloc(sizeof(char) * 6)) == NULL)
		return (ft_puterr("Malloc 3 fail in fill_flag\n"));
	(*flag)[1][0] = '\0';
	return (0);
}

int			init_lie(char ***lie)
{
	if (!(*lie = malloc(sizeof(char *) * 2)) ||
		!((*lie)[0] = malloc(sizeof(char) * 1)) ||
		!((*lie)[1] = malloc(sizeof(char) * 1)))
		return (-1);
	(*lie)[0][0] = 0;
	(*lie)[1][0] = 0;
	return (0);
}
