/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:03:29 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/14 01:16:26 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ls.h"

int			add_elem_before(void *new, t_list **old)
{
	t_list	*new_elem;

	if ((new_elem = malloc(sizeof(t_list))) == NULL)
		return (-1);
	new_elem->content = (void *)new;
	new_elem->prev = NULL;
	new_elem->next = NULL;
	if ((*old)->prev == NULL)
		ft_lstadd_double(old, new_elem);
	else
	{
		new_elem->next = *old;
		new_elem->prev = (*old)->prev;
		(*old)->prev->next = new_elem;
		(*old)->prev = new_elem;
	}
	return (0);
}

int			insert_elem_repo_n_t(t_dn *dn, char **flag,
									t_list *list, t_list **place)
{
	int		ret;
	t_dn	*dn1;

	dn1 = list->content;
	if ((ret = cmp_for_ls(&dn->time, &dn1->time, flag, 0)) < 0)
	{
		if (add_elem_before(dn, &list) == -1)
			return (-1);
		while ((*place)->prev)
			*place = (*place)->prev;
		return (0);
	}
	if (ret == 0)
		if (cmp_for_ls(dn->name, dn1->name, flag, 1) <= 0)
		{
			if (add_elem_before(dn, &list) == -1)
				return (-1);
			while ((*place)->prev)
				*place = (*place)->prev;
			return (0);
		}
	return (1);
}

int			insert_elem_repo_n(t_list **place, t_dn *dn,
								char **flag, t_list *list)
{
	int		ret1;
	t_dn	*dn1;

	list = *place;
	while (list)
	{
		dn1 = list->content;
		if (ft_strstr(flag[1], "t") && flag[1][0] != 0)
		{
			if ((ret1 = insert_elem_repo_n_t(dn, flag, list, place)) == -1)
				return (-1);
			if (ret1 == 0)
				return (0);
		}
		else if (cmp_for_ls(dn->name, dn1->name, flag, 0) <= 0)
		{
			if (add_elem_before(dn, &list) == -1)
				return (-1);
			while ((*place)->prev)
				*place = (*place)->prev;
			return (0);
		}
		list = list->next;
	}
	return (1);
}

int			insert_elem_repo(t_list **place, t_dn *dn, char **flag)
{
	int		ret;
	t_list	*list;

	list = NULL;
	if (*place == NULL)
	{
		if (list_push_back(place, (void *)dn, sizeof(t_dn)) == -1)
			return (ft_puterr("list_push_back fail in main\n"));
		return (0);
	}
	if ((ret = insert_elem_repo_n(place, dn, flag, list)) == -1)
		return (-1);
	if (ret == 0)
		return (0);
	if (list_push_back(place, (void *)dn, sizeof(t_dn)) == -1)
		return (ft_puterr("list_push_back fail in main\n"));
	while ((*place)->prev)
		*place = (*place)->prev;
	return (0);
}
