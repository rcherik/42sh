/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:55:21 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 13:08:09 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "term42.h"
#include <stdlib.h>

char	*ft_get_env(char ***environ, char *want)
{
	int		i;
	char	*tmp;
	char	**env;
	char	*tmp2;

	tmp2 = ft_strdup(want);
	i = 0;
	env = (!environ) ? NULL : *environ;
	want = ft_strjoin(want, "=");
	while (env && env[i])
	{
		if (ft_strnequ(want, env[i], ft_strclen(env[i], '=')))
		{
			ft_strdel(&tmp2);
			tmp = ft_strsub(env[i], ft_strlen(want), ft_strlen(env[i]));
			ft_strdel(&want);
			return (tmp);
		}
		i++;
	}
	ft_strdel(&want);
	return (ft_get_set(tmp2));
}

char	*ft_get_last(char *s)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!s || !s[0])
		return (NULL);
	while (s[i])
		i++;
	j = i;
	i = i - 1;
	while (s[i] != '/' && i > 0)
		i--;
	if (i == j)
		i--;
	if (s[i] != '/')
		return (s);
	tmp = ft_strjoin(ft_sub(s, i + 1, j), "/");
	free(s);
	return (tmp);
}

char	**ft_init_env(char **env)
{
	char	**ret;

	if (!env || !env[0])
	{
		ret = (char **)malloc(sizeof(char *) * 1);
		ret[0] = 0;
	}
	else
		ret = ft_tabdup(env);
	return (ret);
}
