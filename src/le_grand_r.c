/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_grand_r.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:58:39 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 18:58:41 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ls.h"

static t_dn		*check_first(t_list *tmp, char **flag)
{
	t_dn	*dn;

	if (!tmp->prev)
	{
		if (fill_struct(tmp, flag) == -1)
			return (NULL);
		if (flag[0][7] == 0)
			sort_file(&tmp, flag);
		flag[0][7] = 1;
	}
	dn = tmp->content;
	return (dn);
}

int				action_per_repo(t_list *tmp, char **flag)
{
	t_dn	*dn;
	t_dn	*new;
	t_list	*ficon;
	t_fi	*fi;

	if ((dn = check_first(tmp, flag)) == NULL)
		return (-1);
	ficon = dn->files;
	while (ficon)
	{
		fi = ficon->content;
		if (fi->droit[0] == 'd' && (ft_strcmp(fi->name, ".") != 0
								&& ft_strcmp(fi->name, "..") != 0))
		{
			if ((new = malloc(sizeof(t_dn))) == NULL)
				return (ft_puterr("malloc fail in main\n"));
			if ((new->name = ft_strdup(fi->path)) == NULL)
				return (ft_puterr("ft_strdup fail in main\n"));
			new->time = fi->time;
			if (insert_elem_repo(&dn->recur, new, flag) == -1)
				return (ft_puterr("list_push_back fail in main\n"));
		}
		ficon = ficon->next;
	}
	return (0);
}

void			le_grand_r_n(t_list *dir, char **flag, t_dn *dn)
{
	if (dir)
	{
		dn = dir->content;
		if (!dir->next)
		{
			free_dir(dir);
			dir = NULL;
		}
		else
		{
			dir = dir->next;
			free_dir(dir->prev);
		}
		le_grand_r(dir, flag);
	}
}

int				le_grand_r(t_list *dir, char **flag)
{
	t_dn	*dn;
	t_list	*tmp;

	dn = NULL;
	if (dir)
	{
		dn = dir->content;
		action_per_repo(dir, flag);
		disp_for_dir(dir, flag);
		free_fi(dir);
		flag[0][6] = 1;
		tmp = dir;
		dn = dir->content;
		dir = dn->recur;
		le_grand_r(dir, flag);
		dir = tmp;
	}
	le_grand_r_n(dir, flag, dn);
	return (0);
}
