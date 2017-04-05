/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 17:49:52 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/25 00:23:29 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "term42.h"
#include "globbing.h"
#include "curl.h"
#include <stdlib.h>

static int	check_char(char c)
{
	if (c == '*' || c == ']' || c == '[' ||
			c == '{' || c == '}' || c == '?' || c == '<' ||
			c == '>' || c == '!' || c == '@' || c == '#' ||
			c == '$' || c == '^' || c == '&' || c == ' ' ||
			c == 34 || c == 39 || c == '`' || c == '$' || c == 63)
		return (1);
	return (0);
}

char		*ft_bs_chars(char *s)
{
	int			i;
	char		*tmp;

	i = 0;
	while (s[i])
	{
		if (check_char(s[i]) && ft_inhib(s, i))
		{
			tmp = ft_strjoin_slash(s, i);
			s = tmp;
			i++;
		}
		i++;
	}
	return (s);
}

char		*ft_put_backslash(char *sub, char *s, int *end, int start)
{
	char	*tmp;
	char	*tmp_free;
	int		i;

	i = 0;
	tmp = ft_bs_chars(sub);
	tmp_free = s;
	if (ft_isop(s[i], "\"'"))
		i++;
	s = ft_strtjoin(ft_sub(s, i, start), tmp, s + *end + 1);
	ft_strdel(&tmp_free);
	ft_strdel(&tmp);
	*end -= 2;
	return (s);
}

char		*ft_unquote(char *s)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (s[i])
	{
		if (ft_isop(s[i], "\"'") && ft_inhib(s, i))
		{
			j = i;
			tmp = s[i++];
			while ((s[i] && s[i] != tmp) || (s[i] == tmp && !ft_inhib(s, i)))
				i++;
			s = ft_put_backslash(ft_strsub(s, j + 1, i), s, &i, j);
		}
		i++;
	}
	return (s);
}

char		**ft_init_transform(char **tab)
{
	int		i;
	int		j;
	char	**free_tab;

	i = 0;
	free_tab = NULL;
	while (tab[i])
	{
		j = i;
		tab[i] = ft_remove_char(tab[i], 34);
		tab[i] = ft_remove_char(tab[i], 39);
		free_tab = ft_start_curl(tab[i], &i);
		tab = ft_add_tab_curl(tab, free_tab, j);
		free(free_tab);
	}
	return (tab);
}
