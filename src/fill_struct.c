/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 18:09:34 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 18:58:29 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "ls.h"

int					insert_info_file(t_list *dir, DIR *inf_dir, char **flag)
{
	t_dn			*dn;
	struct dirent	*dir_inf;

	dir_inf = NULL;
	dn = dir->content;
	if (dn->bad == FILE)
	{
		if (info_l(dn, dir_inf, flag) == -1)
			return (-1);
	}
	else
	{
		while ((dir_inf = readdir(inf_dir)))
		{
			if ((dir_inf->d_name[0] != '.') ||
					(dir_inf->d_name[0] == '.' && ft_strstr(flag[1], "a")
					&& flag[1][0] != 0))
				if (info_l(dn, dir_inf, flag) == -1)
					return (-1);
		}
	}
	return (0);
}

int					check_file_first(t_dn *dn)
{
	struct stat		buf;

	dn->files = 0;
	dn->recur = NULL;
	dn->total = 0;
	if (lstat(dn->name, &buf) == -1)
	{
		dn->bad = -1;
		dn->recur = 0;
		dn->files = 0;
		return (-1);
	}
	dn->time = buf.st_mtime;
	dn->files = NULL;
	return (0);
}

int					open_fail(t_list *dir, t_dn *dn, char **flag, DIR *inf_dir)
{
	if (EACCES == errno)
	{
		dn->bad = -1;
		dn->recur = 0;
		dn->files = 0;
		return (-1);
	}
	dn->bad = FILE;
	if (insert_info_file(dir, inf_dir, flag) == -1)
		return (-1);
	return (0);
}

int					check_file(t_list *dir, char **flag)
{
	DIR				*inf_dir;
	t_dn			*dn;

	dn = dir->content;
	if (check_file_first(dn) == -1)
		return (-1);
	errno = 0;
	if ((inf_dir = opendir(dn->name)) == NULL)
	{
		if (open_fail(dir, dn, flag, inf_dir) == -1)
			return (-1);
	}
	else
	{
		dn->bad = REPO;
		if (insert_info_file(dir, inf_dir, flag) == -1)
			return (-1);
		closedir(inf_dir);
		return (0);
	}
	return (0);
}

int					fill_struct(t_list *dir, char **flag)
{
	while (dir)
	{
		check_file(dir, flag);
		dir = dir->next;
	}
	return (0);
}
