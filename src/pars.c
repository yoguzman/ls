/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 15:26:02 by yguzman           #+#    #+#             */
/*   Updated: 2017/02/02 15:40:59 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include <errno.h>
#include "libft.h"

static int		check_one_flag(char **flag, char arg)
{
	int			k;
	int			i;

	k = 0;
	while (flag[0][k])
	{
		if (flag[0][k] == arg)
		{
			i = 0;
			while (flag[1][i])
			{
				if (flag[1][i] == flag[0][k])
					return (0);
				++i;
			}
			flag[1][i] = flag[0][k];
			flag[1][i + 1] = '\0';
			return (0);
		}
		++k;
	}
	return (-1);
}

static int		check_all_flag(char **flag, char *arg)
{
	int			i;

	i = 1;
	while (arg[i])
	{
		if (check_one_flag(flag, arg[i]) == -1)
			break ;
		++i;
	}
	if (arg[i] == '\0')
		return (0);
	ft_puterr("ft_ls : illegal option -- ");
	ft_putchar_fd(arg[i], 2);
	ft_putchar_fd('\n', 2);
	return (ft_puterr(USAGE));
}

int				pars_arg_n(t_list **dir, t_list **trash, char *av)
{
	t_dn		*dn;
	char		**lie;
	struct stat	buf;

	lie = NULL;
	if (init_lie(&lie) == -1)
		return (-1);
	if ((dn = malloc(sizeof(t_dn))) == NULL)
		return (ft_puterr("malloc fail in pars_arg\n"));
	if ((dn->name = ft_strdup(av)) == NULL)
		return (ft_puterr("ft_strdup fail in pars arg\n"));
	if (stat(dn->name, &buf) == -1)
	{
		if (errno == ENOENT)
		{
			if (insert_elem_repo(trash, dn, &(*lie)) == -1)
				return (-1);
		}
		else if (list_push_back(dir, (void *)dn, sizeof(t_dn)) == -1)
			return (ft_puterr("list_push_back fail in pars_arg\n"));
	}
	else if (list_push_back(dir, (void *)dn, sizeof(t_dn)) == -1)
		return (ft_puterr("list_push_back fail in pars_arg\n"));
	free_tab(lie);
	return (0);
}

int				disp_trash(t_list *trash, char **flag)
{
	t_list		*tmp;
	t_dn		*dn;
	int			i;

	i = 0;
	while (trash)
	{
		dn = trash->content;
		ft_putstr("ft_ls: ");
		ft_putstr(dn->name);
		flag[0][6] = 2;
		ft_putstr(": No such file or directory\n");
		free(dn->name);
		free(dn);
		tmp = trash;
		trash = trash->next;
		free(tmp);
		tmp = NULL;
		++i;
	}
	return (i);
}

int				pars_arg(int ac, char **av, char **flag, t_list **dir)
{
	int			i;
	t_list		*trash;

	trash = NULL;
	if (ac == 1)
		return (0);
	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-' && av[i][1])
		{
			if (check_all_flag(flag, av[i]) == -1)
				return (-1);
		}
		else
		{
			if (pars_arg_n(dir, &trash, av[i]) == -1)
				return (-1);
			errno = 0;
		}
		++i;
	}
	return (disp_trash(trash, flag));
}
