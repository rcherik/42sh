/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grammar_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 21:36:16 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 02:12:17 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "curl.h"

int		ft_isop(char c, char const *gram)
{
	int	i;

	i = 0;
	while (gram[i])
	{
		if (c == gram[i])
			return (1);
		i++;
	}
	return (0);
}

int		ft_isdoubleop(char *s, char const *gram)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(gram);
	if (ft_strlen(s) != 2)
		return (0);
	while (i < len)
	{
		j = 0;
		if (s[j] == gram[i] && s[j + 1] == gram[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_loop_gram(char *s, int *i)
{
	char	c;
	char	tmp;

	if (*i > 0 && *i - 1 >= 0 && s[*i - 1] == '/')
		return ;
	c = s[*i];
	tmp = c;
	c = (c == '[' ? ']' : c);
	c = (c == '{' ? '}' : c);
	c = (c == '(' ? ')' : c);
	*i += 1;
	while (s[*i] && (s[*i] != c || !ft_inhib(s, *i)))
	{
		if (s[*i] == tmp && ft_inhib(s, *i))
			ft_loop_gram(s, i);
		*i += 1;
	}
}

void	ft_loop_gram_and_fill(char *s, int *i, char *tmp, int *j)
{
	char	c;
	char	orig;

	c = s[*i];
	orig = c;
	tmp[*j] = c;
	c = (c == '[' ? ']' : c);
	c = (c == '{' ? '}' : c);
	c = (c == '(' ? ')' : c);
	*i += 1;
	*j += 1;
	while (s[*i] && (s[*i] != c || ft_inhib(s, *i)))
	{
		tmp[*j] = s[*i];
		*j += 1;
		*i += 1;
		if (s[*i] == orig)
			ft_loop_gram_and_fill(s, i, tmp, j);
	}
	tmp[*j] = s[*i];
}

int		count_bq(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '`' && ft_inhib(s, i))
			count++;
		i++;
	}
	return (count);
}
