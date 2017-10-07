/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:00:22 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 19:04:48 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "libft.h"

int				check_first(t_list *tmp)
{
	t_dn		*dn;

	dn = tmp->content;
	while (tmp->prev && dn->bad == 1)
	{
		tmp = tmp->prev;
		dn = tmp->content;
	}
	if (dn->bad == 0)
		return (0);
	if (tmp->prev == NULL)
		return (1);
	return (0);
}

void			sort_file_and_repo(t_list **dir)
{
	t_list		*tmp;
	t_dn		*dn;

	tmp = *dir;
	while (tmp)
	{
		dn = tmp->content;
		if (dn->bad == 1)
		{
			if (check_first(tmp) == 0)
			{
				ft_lstdel_double(dir, tmp);
				ft_lstadd_double(dir, tmp);
			}
		}
		tmp = tmp->next;
	}
}

void			put_nb_maillon(t_list *dir)
{
	t_dn		*dn;
	int			i;
	int			j;
	t_list		*tmp1;
	t_list		*files;

	i = 0;
	while (dir)
	{
		dn = dir->content;
		files = dn->files;
		tmp1 = files;
		dir->nb = i;
		j = 0;
		while (tmp1)
		{
			tmp1->nb = j;
			tmp1 = tmp1->next;
			++j;
		}
		dir = dir->next;
		++i;
	}
}

void			swap_lol(char **flag, t_dn **dn, t_list **dir, t_dn **dn2)
{
	if (ft_strstr(flag[1], "t") && flag[1][0] != 0)
	{
		if (cmp_for_ls(&(*dn)->time, &(*dn2)->time, flag, 0) > 0)
			ft_swap_list(*dir, (*dir)->next);
	}
	else if (cmp_for_ls((*dn)->name, (*dn2)->name, flag, 0) > 0)
		ft_swap_list(*dir, (*dir)->next);
	*dir = (*dir)->next;
	*dn = (*dir)->content;
	if (*dir && (*dir)->next)
		*dn2 = (*dir)->next->content;
}

void			sort_file(t_list **dir, char **flag)
{
	sort_file_and_repo(dir);
	put_nb_maillon(*dir);
	sort_without_flag(*dir, flag);
}
