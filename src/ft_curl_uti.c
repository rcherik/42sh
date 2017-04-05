/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_curl_uti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 02:06:01 by jbail             #+#    #+#             */
/*   Updated: 2014/03/15 19:06:42 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "curl.h"

int		ft_count_curl(char *s)
{
	int		i;
	int		match;

	i = 0;
	while (s[i])
	{
		if (s[i] == '{' && !(i > 0 && s[i - 1] == '\\'))
		{
			match = 0;
			while ((i > 0 && s[i] == '}' && s[i - 1] == '\\')
					|| (s[i] != '}' && s[i] != '\0'))
			{
				if (s[i] == ',')
					match++;
				i++;
			}
			if (s[i] == '}' && match > 0)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int		ft_check_bracket(char *s, int i, int *pos)
{
	int		comma;

	comma = 0;
	*pos = 0;
	while (s[i])
	{
		if (s[i] == ',')
			comma++;
		if (s[i] == '}')
			break ;
		i++;
		(*pos)++;
	}
	if (!s[i] || !comma)
		return (0);
	return (1);
}

int		ft_count_commas(char **tab, char *s)
{
	int		i;
	int		count;
	int		tablen;

	tablen = ft_tlen(tab);
	i = 0;
	count = 1;
	while (s[i])
	{
		if (s[i] == ',')
			count++;
		i++;
	}
	return (count * tablen);
}

int		ft_correct_curl(char *s, int i)
{
	int		comma;

	comma = 0;
	while (s[i])
	{
		if (s[i] == ',')
			comma++;
		if (s[i] == '}' && !(i > 0 && s[i - 1] == '\\'))
			return (comma);
		i++;
	}
	return (0);
}
