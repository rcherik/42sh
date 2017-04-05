/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_globbing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 13:22:26 by jbail             #+#    #+#             */
/*   Updated: 2014/03/27 18:17:49 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"
#include "term42.h"
#include <stdlib.h>

int			ft_globbing_add(char *opt, t_files *files, char ***tab)
{
	int			match;
	t_files		*tmp;

	tmp = files;
	match = 0;
	while (tmp && files)
	{
		if (ft_first_match(opt, tmp->file))
		{
			*tab = ft_add_to_opts(*tab, tmp->file);
			match = 1;
		}
		tmp = tmp->next;
	}
	return (match);
}

static int	ft_remove_bs_count(char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != '\\')
			count++;
		if (s[i] == '\\' && s[i + 1] == '\\')
		{
			i++;
			count++;
		}
		i++;
	}
	return (count + 1);
}

char		*ft_remove_bs(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = (char *)malloc(ft_remove_bs_count(s));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\\')
			tmp[j++] = s[i];
		if (s[i] == '\\' && s[i + 1] == '\\')
		{
			tmp[j++] = '\\';
			i++;
		}
		i++;
	}
	tmp[j] = '\0';
	free(s);
	return (tmp);
}

char		**ft_glob(char *opts, t_files *files)
{
	char		**tab;
	int			match;
	static int	lim;

	lim = 0;
	tab = NULL;
	match = 0;
	if (ft_check_chars(opts, "?*["))
	{
		if (!ft_check_slash(opts))
			match = ft_globbing_add(opts, files, &tab);
		else
			match = ft_get_files_from_dir(opts, &tab, &lim);
	}
	if (match == -1)
	{
		free(opts);
		return (NULL);
	}
	if (!match)
		return (ft_no_match(opts));
	free(opts);
	return (tab);
}

char		**ft_start_globbing(char *s)
{
	char	**tab;
	char	*set_g;
	t_files	*list;
	t_shell	*shell;

	shell = ft_return_shell(NULL, NULL);
	set_g = NULL;
	list = NULL;
	if ((set_g = ft_get_env(shell->env, "GLOBBING")) && (ft_atoi(set_g) > 0))
	{
		list = ft_init_files(".");
		if (!(tab = ft_glob(s, list)))
		{
			ft_free_files(list);
			free(set_g);
			return (NULL);
		}
		ft_free_files(list);
	}
	else
		tab = ft_no_match(s);
	free(set_g);
	return (tab);
}
