/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:15:46 by yguzman           #+#    #+#             */
/*   Updated: 2017/04/13 18:54:47 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <sys/stat.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include "libft.h"

# define FILE 1
# define REPO 0
# define BAD 2
# define USAGE "usage : ./ft_ls [-Rrtal] [file ...]\n"

typedef struct		s_files_info
{
	char			*path;
	char			*name;
	char			*droit;
	int				lien;
	char			*user;
	char			*groupe;
	int				majeur;
	int				mineur;
	int				size;
	char			*date;
	time_t			time;
	char			lien_name[300];
}					t_fi;

typedef struct		s_dir_name
{
	char			*name;
	t_list			*recur;
	t_list			*files;
	int				total;
	time_t			time;
	int				bad;
	int				nb;
}					t_dn;

void				disp_for_dir(t_list *dir, char **flag);
int					info_l(t_dn *dn, struct dirent *inf_dir, char **flag);
int					pars_arg(int ac, char **av, char **flag, t_list **dir);
int					fill_flag(char ***flag);
int					fill_struct(t_list *dir, char **flag);
char				*stick_file(char *parent, char *file);
void				sort_file(t_list **dir, char **flag);
void				ft_swap_list(t_list *a, t_list *b);
void				sort_without_flag(t_list *dir, char **flag);
void				rev_list(t_list *a, t_list *b);
int					cmp_for_ls(void *s1, void *s2, char **flag, int check);
int					le_grand_r(t_list *dir, char **flag);
int					insert_elem_file(t_list **place, t_fi *fi, char **flag);
int					insert_elem_repo(t_list **place, t_dn *dn, char **flag);
void				free_dir(t_list *dir);
void				free_fi(t_list *dir);
void				free_tab(char **flag);
void				free_dir(t_list *dir);
void				free_fi(t_list *dir);
void				swap_lol(char **flag, t_dn **dn, t_list **dir, t_dn **dn2);
int					init_lie(char ***lie);
int					add_elem_before(void *new, t_list **old);
void				ft_putstr_ls(t_fi *fi);

#endif
