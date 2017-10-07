/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:56:51 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 18:57:56 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ls.h>

void			free_fi_all(t_fi *fi, t_dn *dn, t_list *file)
{
	fi = file->content;
	if (dn->bad != FILE)
		free(fi->path);
	free(fi->name);
	free(fi->droit);
	free(fi->date);
	free(fi);
}

void			free_fi(t_list *dir)
{
	t_dn		*dn;
	t_fi		*fi;
	t_list		*file;
	t_list		*tmp;

	dn = dir->content;
	file = dn->files;
	if (file)
		fi = file->content;
	while (file && fi)
	{
		free_fi_all(fi, dn, file);
		if (!file->next)
		{
			free(file);
			file = NULL;
		}
		else
		{
			tmp = file;
			file = file->next;
			fi = file->content;
			free(tmp);
		}
	}
}

void			free_dir(t_list *dir)
{
	t_dn		*dn;

	dn = dir->content;
	if (dn->bad != FILE)
		free(dn->name);
	free(dn);
	free(dir);
}

void			free_tab(char **flag)
{
	free(flag[0]);
	free(flag[1]);
	free(flag);
}
