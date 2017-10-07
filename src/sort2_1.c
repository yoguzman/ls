/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort2_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:03:34 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 19:06:19 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ls.h"
#include "libft.h"

int			insert_elem_file_n_t(t_fi *fi, char **flag,
									t_list *list, t_list **place)
{
	int		ret;
	t_fi	*fi1;

	fi1 = list->content;
	if ((ret = cmp_for_ls(&fi->time, &fi1->time, flag, 0)) < 0)
	{
		if (add_elem_before(fi, &list) == -1)
			return (-1);
		while ((*place)->prev)
			*place = (*place)->prev;
		return (0);
	}
	if (ret == 0)
		if (cmp_for_ls(fi->name, fi1->name, flag, 1) <= 0)
		{
			if (add_elem_before(fi, &list) == -1)
				return (-1);
			while ((*place)->prev)
				*place = (*place)->prev;
			return (0);
		}
	return (1);
}

int			insert_elem_file_n(t_list **place, t_fi *fi,
								char **flag, t_list *list)
{
	int		ret1;
	t_fi	*fi1;

	list = *place;
	while (list)
	{
		fi1 = list->content;
		if (ft_strstr(flag[1], "t") && flag[1][0] != 0)
		{
			if ((ret1 = insert_elem_file_n_t(fi, flag, list, place)) == -1)
				return (-1);
			if (ret1 == 0)
				return (0);
		}
		else if (cmp_for_ls(fi->name, fi1->name, flag, 0) <= 0)
		{
			if (add_elem_before(fi, &list) == -1)
				return (-1);
			while ((*place)->prev)
				*place = (*place)->prev;
			return (0);
		}
		list = list->next;
	}
	return (1);
}

int			insert_elem_file(t_list **place, t_fi *fi, char **flag)
{
	int		ret;
	t_list	*list;

	list = NULL;
	if (*place == NULL)
	{
		if (list_push_back(place, (void *)fi, sizeof(t_fi)) == -1)
			return (ft_puterr("list_push_back fail in main\n"));
		return (0);
	}
	if ((ret = insert_elem_file_n(place, fi, flag, list)) == -1)
		return (-1);
	if (ret == 0)
		return (0);
	if (list_push_back(place, (void *)fi, sizeof(t_fi)) == -1)
		return (ft_puterr("list_push_back fail in main\n"));
	while ((*place)->prev)
		*place = (*place)->prev;
	return (0);
}
