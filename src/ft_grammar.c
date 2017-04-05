/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grammar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 20:59:10 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 07:05:17 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "curl.h"

static void	ft_space_it(char **s, char **tmp, int *i, int *j)
{
	(*tmp)[*j] = ' ';
	*j += 1;
	(*tmp)[*j] = (*s)[*i];
	*i += 1;
	*j += 1;
	while ((*s)[*i - 1] && (*s)[*i] && (*s)[*i - 1] == (*s)[*i])
	{
		(*tmp)[*j] = (*s)[*i];
		*i += 1;
		*j += 1;
	}
	(*tmp)[*j] = ' ';
	*j += 1;
}

static char	*ft_tab_to_space(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] && ft_isop(s[i], "\"'`([{") && ft_inhib(s, i))
			ft_loop_gram(s, &i);
		if (ft_isspace(s[i]) && s[i] != ' ')
			s[i] = ' ';
		i++;
	}
	return (s);
}

static char	*ft_epur_quoteless(char *s)
{
	int		i;
	int		j;
	char	*tmp;
	char	*ret;

	i = -1;
	j = 0;
	tmp = ft_strnew(ft_strlen(s) + 1);
	while (s[++i])
	{
		while (s[i] && ft_isspace(s[i]) && ft_isspace(s[i + 1])
				&& ft_inhib(s, i) && ft_inhib(s, i + 1))
			i++;
		if (s[i] && ft_isop(s[i], "\"'`({[") && ft_inhib(s, i))
			ft_loop_gram_and_fill(s, &i, tmp, &j);
		tmp[j] = s[i];
		j++;
	}
	tmp[j] = 0;
	ret = ft_strtrim(tmp);
	ft_strdel(&tmp);
	ret = ft_tab_to_space(ret);
	return (ret);
}

char		*ft_epur_grammar(char *s, char const *gram)
{
	int		i;
	int		j;
	char	*tmp;
	char	*ret;
	int		len;

	i = 0;
	j = 0;
	if (!*s)
		return (NULL);
	len = ft_strlen(s);
	tmp = ft_strnew(2 * len + 1);
	while (s && i < len && j < (2 * len + 1))
	{
		if (ft_isop(s[i], gram) && ft_inhib(s, i))
			ft_space_it(&s, &tmp, &i, &j);
		else
			tmp[j++] = s[i++];
	}
	tmp[j] = '\0';
	ret = ft_epur_quoteless(tmp);
	ft_strdel(&tmp);
	ft_strdel(&s);
	return (ret);
}
