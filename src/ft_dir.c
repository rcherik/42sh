/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 13:25:51 by jbail             #+#    #+#             */
/*   Updated: 2014/03/27 18:17:51 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"
#include "curl.h"
#include <stdlib.h>

char	**ft_get_dirs(char *path, char *opt, int *match, int *lim)
{
	char	**tmp;
	t_files	*files;

	tmp = NULL;
	if ((files = ft_init_files_dir(path, lim)) != NULL)
	{
		*match = ft_globbing_add(opt, files, &tmp);
		ft_free_files(files);
	}
	else
	{
		ft_free_tabcpy(tmp);
		return (NULL);
	}
	return (tmp);
}

char	**ft_init_dirs(char *s)
{
	char	**dirs;

	dirs = (char **)malloc(sizeof(char *) * 2);
	if (s[0] == '/')
	{
		dirs[0] = ft_strnew(2);
		dirs[0][0] = '/';
	}
	else
		dirs[0] = ft_strnew(1);
	dirs[1] = NULL;
	return (dirs);
}

char	**ft_get_new_dirs(char **c_dir, char *old_dir, char **tab)
{
	int		i;
	char	*tmp2;

	i = 0;
	while (c_dir[i])
	{
		tmp2 = ft_strjoin_and_char(old_dir, c_dir[i], '/');
		free(c_dir[i]);
		c_dir[i] = tmp2;
		i++;
	}
	tab = ft_add_tab(tab, c_dir);
	free(c_dir);
	return (tab);
}

char	**ft_process_dirs(char **d, char *opt, int *match, int *l)
{
	int		i;
	char	**tab;
	char	**tmp;

	i = 0;
	tab = NULL;
	tmp = NULL;
	while (d[i])
	{
		tab = ft_get_dirs(d[i], opt, match, l);
		if (*l == -1)
		{
			ft_free_tabcpy(d);
			ft_free_tabcpy(tab);
			ft_free_tabcpy(tmp);
			return (NULL);
		}
		if (tab)
			tmp = ft_get_new_dirs(tab, d[i], tmp);
		i++;
	}
	ft_free_tabcpy(d);
	return (tmp);
}

int		ft_get_files_from_dir(char *s, char ***tab, int *lim)
{
	int		i;
	int		match;
	char	**splits;

	i = 0;
	match = 1;
	*tab = ft_init_dirs(s);
	splits = ft_strsplit(s, '/');
	while (splits[i] && !ft_check_chars(splits[i], "[*?"))
		(*tab)[0] = ft_strjoin_char_free_first((*tab)[0], splits[i++], '/');
	while (splits[i] && match)
	{
		match = 0;
		*tab = ft_process_dirs(*tab, splits[i], &match, lim);
		if ((!*tab) && *lim == -1)
		{
			ft_free_tabcpy(splits);
			return ((ft_error("Argument list too long", NULL)) * -1);
		}
		i++;
	}
	ft_free_tabcpy(splits);
	return (match);
}
