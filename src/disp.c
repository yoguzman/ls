/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 15:27:43 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 18:56:08 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		ft_putstr_date(char *date)
{
	int		i;

	i = 0;
	ft_putchar(date[8]);
	ft_putchar(date[9]);
	ft_putchar(' ');
	ft_putchar(date[4]);
	ft_putchar(date[5]);
	ft_putchar(date[6]);
	ft_putchar(' ');
	ft_putchar(date[11]);
	ft_putchar(date[12]);
	ft_putchar(date[13]);
	ft_putchar(date[14]);
	ft_putchar(date[15]);
}

void		disp_ls_l_n(t_fi *fi)
{
	ft_putstr(fi->droit);
	ft_putchar(' ');
	ft_putnbr(fi->lien);
	ft_putchar(' ');
	if (fi->user)
		ft_putstr(fi->user);
	ft_putchar(' ');
	if (fi->groupe)
		ft_putstr(fi->groupe);
	ft_putchar(' ');
}

void		disp_ls_l(t_fi *fi)
{
	disp_ls_l_n(fi);
	if (fi->droit[0] == 'c' || fi->droit[0] == 'b')
	{
		ft_putnbr(fi->majeur);
		ft_putstr(", ");
		ft_putnbr(fi->mineur);
	}
	else
		ft_putnbr(fi->size);
	ft_putchar(' ');
	if (fi->date)
		ft_putstr_date(fi->date);
	ft_putchar(' ');
	ft_putstr_ls(fi);
	if ((fi->droit)[0] == 'l')
	{
		ft_putstr(" -> ");
		ft_putstr(fi->lien_name);
	}
	ft_putchar('\n');
}

void		disp_for_dir_n(t_dn *dn, char **flag, t_list *file, t_fi *fi)
{
	char	*ret;

	if ((ret = ft_strstr(flag[1], "l")) && flag[1][0] && file && dn->bad == 0)
	{
		ft_putstr("total ");
		ft_putnbr(dn->total);
		ft_putchar('\n');
	}
	if (!file)
		return ;
	while (file)
	{
		fi = file->content;
		if (ret && flag[1][0] != 0)
			disp_ls_l(fi);
		else
		{
			ft_putstr_ls(fi);
			if (file->next)
				ft_putchar('\n');
		}
		file = file->next;
	}
	if (ret == NULL)
		ft_putchar('\n');
}

void		disp_for_dir(t_list *dir, char **flag)
{
	t_dn	*dn;
	t_fi	*fi;
	t_list	*file;

	dn = dir->content;
	if ((flag[0][6] || dir->next) && dn->bad != 1)
	{
		if (flag[0][6] == 1)
			ft_putchar('\n');
		ft_putstr(dn->name);
		ft_putstr(":\n");
	}
	if (dn->bad == -1)
	{
		ft_puterr("ft_ls: ");
		ft_puterr(dn->name);
		ft_puterr(": Permission denied\n");
	}
	else
	{
		file = dn->files;
		fi = file ? file->content : NULL;
		disp_for_dir_n(dn, flag, file, fi);
	}
}
