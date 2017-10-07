/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:23:51 by yguzman           #+#    #+#             */
/*   Updated: 2017/02/07 15:27:30 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include "ls.h"

void			free_all(t_list *dir)
{
	free_fi(dir);
	free_dir(dir);
}

int				ft_ls(t_list *dir, char **flag)
{
	if (ft_strstr(flag[1], "R") && flag[1][0] != 0)
	{
		if (le_grand_r(dir, flag) == -1)
			return (-1);
		return (0);
	}
	if (fill_struct(dir, flag) == -1)
		return (-1);
	sort_file(&dir, flag);
	while (dir)
	{
		disp_for_dir(dir, flag);
		flag[0][6] = 1;
		if (!dir->next)
		{
			free_all(dir);
			dir = NULL;
		}
		else
		{
			dir = dir->next;
			free_all(dir->prev);
		}
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_list		*dir;
	char		**flag;
	t_dn		*dn;
	int			ret;

	dir = NULL;
	if (fill_flag(&flag) == -1 || (ret = pars_arg(ac, av, flag, &dir)) == -1)
		return (-1);
	if (dir == NULL && ret == 0)
	{
		if ((dn = malloc(sizeof(t_dn))) == NULL)
			return (ft_puterr("malloc fail in main\n"));
		if ((dn->name = ft_strdup(".")) == NULL)
			return (ft_puterr("ft_strdup fail in main\n"));
		if (list_push_back(&dir, (void *)dn, sizeof(dn)) == -1)
			return (ft_puterr("list_push_back fail in main\n"));
	}
	if (dir == NULL)
		return (-1);
	if (ft_ls(dir, flag) == -1)
		return (-1);
	free_tab(flag);
	return (0);
}
