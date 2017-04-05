/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 13:39:52 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 09:22:20 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "curl.h"
#include "term42.h"
#include <stdlib.h>

static char		*get_dollar2(char *s, int *x, char ***env)
{
	int			i;
	char		*dal;
	int			y;
	char		*tmp;

	i = 0;
	y = x[0] + 1;
	while (s[y] && s[y] != ' ' && s[y] != 92 && !(s[y] == 34
				|| !ft_inhib(s, y)))
	{
		y++;
		i++;
	}
	if (i == y)
	{
		x[2] = 0;
		return (NULL);
	}
	x[2] = i;
	tmp = ft_strsub_len(s, x[0] + 1, i);
	dal = ft_get_env(env, tmp);
	ft_strdel(&tmp);
	return (dal);
}

static char		*get_dollar(char *s, int *x, char ***env, char *dal)
{
	char		*ret;

	if (s[x[0] + 1] && s[x[0] + 1] == 35 && s[x[0] + 2] && s[x[0] + 2] == '{')
		return (get_dollen(s, x, env));
	if (s[x[0] + 1] && s[x[0] + 1] == 35)
		return (get_dollen2(s, x, env));
	if (s[x[0] + 1] && s[x[0] + 1] == '{')
		return (get_dollar3(s, x, env));
	dal = get_dollar2(s, x, env);
	if (dal == NULL)
	{
		ret = ft_strnew(ft_strlen(s) - x[2]);
		ft_strncpy(ret, s, x[0]);
		ret = ft_strjoin_free(&ret, s + x[0] + x[2] + 1);
		x[0] -= 1;
		ft_strdel(&s);
		return (ret);
	}
	ret = ft_strnew(ft_strlen(s) - x[2] + ft_strlen(dal));
	ft_strncpy(ret, s, x[0]);
	ret = ft_strjoin_free(&ret, dal);
	ret = ft_strjoin_free(&ret, s + x[0] + x[2] + 1);
	x[0] += ft_strlen(dal) - 1;
	ft_double_free(dal, s);
	return (ret);
}

char			*add_bs(char *s, int i, int *ptr)
{
	char		*ret;

	ret = ft_strnew(ft_strlen(s) + 1);
	ft_strncpy(ret, s, i);
	ret[i] = 92;
	ft_strcpy(ret + i + 1, s + i);
	ft_strdel(&s);
	(*ptr)++;
	return (ret);
}

static char		*cocote(char *s, int *x, char ***env)
{
	char		*dal;

	dal = NULL;
	if (x[1] == 0 && s[x[0]] == '$' && ft_inhib(s, x[0]) && s[x[0] + 1])
		return (get_dollar(s, x, env, dal));
	if (x[1] == 2 && s[x[0]] == '$' && ft_inhib(s, x[0]) && s[x[0] + 1] != '"')
		return (get_dollar(s, x, env, dal));
	if (x[1] == 2 && s[x[0]] == '\\' && ft_inhib(s, x[0]) && check_c(s, x[0]))
		return (add_bs(s, x[0], &(x[0])));
	else if (x[1] == 1 && check_char2(s[x[0]]))
		return (add_bs(s, x[0], &(x[0])));
	else if ((x[1] == 2 || x[1] == 0) && s[x[0]] == '`' && ft_inhib(s, x[0]))
		return (add_bq(s, x, env));
	else if (x[1] == 2 && check_char3(s[x[0]]) && ft_inhib(s, x[0]))
		return (add_bs(s, x[0], &(x[0])));
	return (s);
}

char			*ft_quotes(char *s, char ***env)
{
	int			x[3];

	ft_init_tabint(x, 3);
	while (s[x[0]])
	{
		if ((s[x[0]] == 39 && ft_inhib(s, x[0]))
				|| (s[x[0]] == 39 && x[1] == 1))
			x[1] = (x[1] == 0) ? 1 : 0;
		else if (s[x[0]] == 34 && ft_inhib(s, x[0]))
			x[1] = (x[1] == 0) ? 2 : 0;
		s = cocote(s, x, env);
		if (!s)
			return (NULL);
		x[0]++;
	}
	return (s);
}
