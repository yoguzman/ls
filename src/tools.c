/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:03:43 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 19:07:17 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void				ft_swap_list(t_list *a, t_list *b)
{
	void			*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

long				cmp_for_ls(void *s1, void *s2, char **flag, int check)
{
	unsigned char	*t1;
	unsigned char	*t2;
	long			a;
	long			b;

	if (check == 0)
	{
		if (ft_strstr(flag[1], "t") && flag[1][0] != 0)
		{
			a = *(long *)s1;
			b = *(long *)s2;
			if (ft_strstr(flag[1], "r") && flag[1][0] != 0)
				return (a - b);
			return (b - a);
		}
	}
	t1 = (unsigned char*)s1;
	t2 = (unsigned char*)s2;
	while (*t1 && *t1 == *t2 && t1++ && t2++)
		;
	if (ft_strstr(flag[1], "r") && flag[1][0] != 0)
		return (*t2 - *t1);
	return (*t1 - *t2);
}

void				rev_list(t_list *a, t_list *b)
{
	while (a->nb < b->nb)
	{
		ft_swap_list(a, b);
		a = a->next;
		b = b->prev;
	}
}

char				*stick_file(char *parent, char *file)
{
	char			*new;
	int				i;
	int				nb;

	i = 0;
	nb = 2;
	while (parent[i])
		++i;
	if (parent[i - 1] == '/')
		nb = 1;
	if ((new = malloc(sizeof(char) *
				(ft_strlen(parent) + ft_strlen(file) + nb))) == NULL)
	{
		ft_puterr("malloc fail in func stick file\n");
		return (NULL);
	}
	new[0] = 0;
	ft_strcat(new, parent);
	if (nb == 2)
		ft_strcat(new, "/");
	ft_strcat(new, file);
	return (new);
}
