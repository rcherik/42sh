/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 14:00:30 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 01:12:47 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "curl.h"
#include <stdlib.h>

static int	ft_splits(char *s)
{
	int	i;
	int	splits;

	i = 0;
	splits = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]) && ft_inhib(s, i)
				&& !ft_isop(s[i], "\"'`({["))
			i++;
		if (s[i] && (!ft_isspace(s[i]) && ft_inhib(s, i)))
			splits++;
		while (s[i] && ((!ft_isspace(s[i]) && !ft_isop(s[i], "\"'`({["))
						|| !ft_inhib(s, i)))
			i++;
		if (s[i] && ft_isop(s[i], "\"'`({[") && ft_inhib(s, i))
		{
			ft_loop_gram(s, &i);
			i++;
		}
		while (s[i] && ((!ft_isspace(s[i]) && !ft_isop(s[i], "\"'`({["))
						|| !ft_inhib(s, i)))
			i++;
	}
	return (splits);
}

static char	*ft_fill_tab(char *s, int *begin)
{
	int		i;
	int		j;
	char	*tmp;

	i = *begin;
	if (s[i] && ft_isspace(s[i]) && ft_inhib(s, i))
		i++;
	j = i;
	while (s[j] && (!ft_isspace(s[j]) || !ft_inhib(s, j)))
	{
		if (s[j] && ft_isop(s[j], "\"'`({[") && ft_inhib(s, j))
			ft_loop_gram(s, &j);
		j++;
	}
	*begin = j;
	tmp = ft_strsub(s, i, j);
	return (tmp);
}

static char	*ft_add_home_from_tilde(char *s, char **env)
{
	int		i;
	int		j;
	char	*home;
	char	*tmp;

	if ((home = ft_get_env(&env, "HOME")) == NULL)
		return (s);
	tmp = (char *)malloc(ft_strlen(home) + ft_strlen(s));
	i = 0;
	while (home[i])
	{
		tmp[i] = home[i];
		i++;
	}
	j = 1;
	while (s[j])
		tmp[i++] = s[j++];
	tmp[i] = '\0';
	free(home);
	free(s);
	return (tmp);
}

char		**ft_quotesplit(char *s, char **env)
{
	int		split;
	int		i;
	char	**tab;
	int		j;

	i = 0;
	j = 0;
	if (s && !*s)
		ft_strdel(&s);
	if (!s)
		return (NULL);
	split = ft_splits(s);
	if (!(tab = (char **)malloc(sizeof(char *) * (split + 1))))
		return (NULL);
	while (split--)
	{
		tab[i] = ft_fill_tab(s, &j);
		if (ft_strequ(tab[i], "~") || ft_strnequ(tab[i], "~/", 2))
			tab[i] = ft_add_home_from_tilde(tab[i], env);
		i++;
	}
	tab[i] = 0;
	free(s);
	return (tab);
}
