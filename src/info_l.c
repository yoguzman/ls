/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 20:28:41 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 19:00:00 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <time.h>
#include <grp.h>
#include "libft.h"
#include "ls.h"

void				fill_min_maj(struct stat buf, t_fi *fi)
{
	fi->droit[1] = buf.st_mode & S_IRUSR ? 'r' : '-';
	fi->droit[2] = buf.st_mode & S_IWUSR ? 'w' : '-';
	fi->droit[3] = buf.st_mode & S_IXUSR ? 'x' : '-';
	fi->droit[4] = buf.st_mode & S_IRGRP ? 'r' : '-';
	fi->droit[5] = buf.st_mode & S_IWGRP ? 'w' : '-';
	fi->droit[6] = buf.st_mode & S_IXGRP ? 'x' : '-';
	fi->droit[7] = buf.st_mode & S_IRGRP ? 'r' : '-';
	fi->droit[8] = buf.st_mode & S_IWGRP ? 'w' : '-';
	fi->droit[9] = buf.st_mode & S_IXGRP ? 'x' : '-';
	if (fi->droit[0] == 'c' || fi->droit[0] == 'b')
	{
		fi->majeur = buf.st_rdev >> 24;
		fi->mineur = buf.st_rdev & 255;
	}
}

int					fill_droit(struct stat buf, t_fi *fi, char *file)
{
	if ((fi->droit = malloc(sizeof(char) * 11)) == NULL)
		return (ft_puterr("malloc fail in fail droit\n"));
	fi->droit[10] = 0;
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
		fi->droit[0] = 'd';
	else if ((buf.st_mode & S_IFMT) == S_IFCHR)
		fi->droit[0] = 'c';
	else if ((buf.st_mode & S_IFMT) == S_IFSOCK)
		fi->droit[0] = 's';
	else if ((buf.st_mode & S_IFMT) == S_IFLNK)
	{
		ft_bzero(fi->lien_name, 300);
		if (readlink(file, fi->lien_name, 299) < 0)
			return (ft_puterr("readlink c est casse\n"));
		fi->droit[0] = 'l';
	}
	else if ((buf.st_mode & S_IFMT) == S_IFREG)
		fi->droit[0] = '-';
	else if ((buf.st_mode & S_IFMT) == S_IFBLK)
		fi->droit[0] = 'b';
	else if ((buf.st_mode & S_IFMT) == S_IFIFO)
		fi->droit[0] = 'p';
	fill_min_maj(buf, fi);
	return (0);
}

int					info_l_one_file_p(t_fi *fi, struct stat buf)
{
	fi->lien = buf.st_nlink;
	fi->user = (getpwuid(buf.st_uid))->pw_name;
	fi->groupe = (getgrgid(buf.st_gid))->gr_name;
	fi->size = buf.st_size;
	if ((fi->date = (ft_strdup(ctime(&buf.st_mtime)))) == NULL)
		return (ft_puterr("ctime fail in function info_l_one_file\n"));
	fi->time = buf.st_mtime;
	return (0);
}

int					info_l_one_file(t_dn *dn, t_fi *fi, char **flag)
{
	struct stat		buf;
	char			*file;

	if (dn->bad == REPO)
	{
		if ((file = stick_file(dn->name, fi->name)) == NULL)
			return (-1);
	}
	else
		file = dn->name;
	fi->path = file;
	if (lstat(file, &buf) == -1)
		return (-1);
	dn->total = dn->total + buf.st_blocks;
	fi->time = buf.st_mtime;
	if (fill_droit(buf, fi, file) == -1)
		return (-1);
	if (ft_strstr(flag[1], "l") && flag[1][0] != 0)
		if (info_l_one_file_p(fi, buf) == -1)
			return (-1);
	return (0);
}

int					info_l(t_dn *dn, struct dirent *inf_dir, char **flag)
{
	t_fi			*fi;

	if ((fi = malloc(sizeof(t_fi))) == NULL)
		return (ft_puterr("malloc fail in func info_l\n"));
	fi->path = NULL;
	fi->droit = NULL;
	fi->user = NULL;
	fi->groupe = NULL;
	fi->date = NULL;
	if (dn->bad == FILE)
		fi->name = dn->name;
	else
	{
		if ((fi->name = ft_strdup(inf_dir->d_name)) == NULL)
			return (-1);
	}
	if (info_l_one_file(dn, fi, flag) == -1)
		return (-1);
	if (insert_elem_file(&(dn->files), fi, flag) == -1)
		return (-1);
	return (0);
}
