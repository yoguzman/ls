/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 13:55:56 by yguzman           #+#    #+#             */
/*   Updated: 2016/07/18 18:56:26 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void			ft_putstr(char const *str)
{
	write(1, str, ft_strlen(str));
}

void			ft_putstr_color(char *str, int color)
{
	ft_putstr("\033[");
	ft_putnbr(color);
	ft_putstr(";01m");
	ft_putstr(str);
	ft_putstr("\033[00m");
}
