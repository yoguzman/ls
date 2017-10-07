/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:02:15 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 19:03:20 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			check_sort_rep(t_list *dir, char **flag)
{
	t_dn	*dn;
	t_dn	*dn2;

	if (dir && dir->next)
	{
		dn = dir->content;
		dn2 = dir->next->content;
	}
	while (dir && dir->next)
	{
		if (ft_strstr(flag[1], "t") && flag[1][0] != 0)
		{
			if (cmp_for_ls(&dn->time, &dn2->time, flag, 0) > 0)
				return (1);
		}
		else if (cmp_for_ls(dn->name, dn2->name, flag, 0) > 0)
			return (1);
		dir = dir->next;
		dn = dir->content;
		if (dir && dir->next)
			dn2 = dir->next->content;
	}
	return (0);
}

void		sort_without_flag_rep(t_list *tmp, char **flag)
{
	t_dn	*dn;
	t_dn	*dn2;
	t_list	*dir;

	dir = tmp;
	if (dir && dir->next)
	{
		dn = dir->content;
		dn2 = dir->next->content;
	}
	while (dir && dir->next)
	{
		if (ft_strstr(flag[1], "t") && flag[1][0] != 0)
		{
			if (cmp_for_ls(&dn->time, &dn2->time, flag, 0) > 0)
				ft_swap_list(dir, dir->next);
		}
		else if (cmp_for_ls(dn->name, dn2->name, flag, 0) > 0)
			ft_swap_list(dir, dir->next);
		dir = dir->next;
		dn = dir->content;
		if (dir && dir->next)
			dn2 = dir->next->content;
	}
	dir = tmp;
}

int			check_sort_file(t_list *dir, char **flag)
{
	t_dn	*dn;
	t_dn	*dn2;

	if (dir && dir->next)
	{
		dn = dir->content;
		dn2 = dir->next->content;
	}
	while (dir && dir->next && dn->bad == 1 && dn2->bad == 1)
	{
		if (ft_strstr(flag[1], "t") && flag[1][0] != 0)
		{
			if (cmp_for_ls(&dn->time, &dn2->time, flag, 0) > 0)
				return (1);
		}
		else if (cmp_for_ls(dn->name, dn2->name, flag, 0) > 0)
			return (1);
		dir = dir->next;
		dn = dir->content;
		if (dir && dir->next)
			dn2 = dir->next->content;
	}
	return (0);
}

void		prep_sort(t_list *tmp, t_dn *dn, char **flag)
{
	dn = tmp->content;
	while (tmp && dn->bad != 0)
	{
		tmp = tmp->next;
		if (tmp)
			dn = tmp->content;
	}
	while (check_sort_rep(tmp, flag))
		sort_without_flag_rep(tmp, flag);
}

void		sort_without_flag(t_list *tmp, char **flag)
{
	t_dn	*dn;
	t_dn	*dn2;
	t_list	*dir;

	dir = tmp;
	while (check_sort_file(dir, flag))
	{
		if (dir && dir->next)
		{
			dn = dir->content;
			dn2 = dir->next->content;
		}
		while (dir && dir->next && dn->bad == 1 && dn2->bad == 1)
			swap_lol(flag, &dn, &dir, &dn2);
		dir = tmp;
	}
	prep_sort(tmp, dn, flag);
}
