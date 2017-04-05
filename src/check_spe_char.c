/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spe_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 18:34:08 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/25 18:34:09 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include <stdlib.h>

int			check_char3(char c)
{
	if (c == '*' || c == ']' || c == '[' ||
			c == '{' || c == '}' || c == '?' || c == '<' ||
			c == '>' || c == '!' || c == '@' || c == '#' ||
			c == '^' || c == '&' || c == ' ' ||
			c == 39 || c == 63 || c == 47)
		return (1);
	return (0);
}

int			check_char2(char c)
{
	if (c == 92 || c == '*' || c == ']' || c == '[' ||
			c == '{' || c == '}' || c == '?' || c == '<' ||
			c == '>' || c == '!' || c == '@' || c == '#' ||
			c == '$' || c == '^' || c == '&' || c == ' ' ||
			c == 34 || c == '`' || c == 63 || c == 47)
		return (1);
	return (0);
}

static int	check_char(char c)
{
	if (c == 92 || c == '*' || c == ']' || c == '[' ||
			c == '{' || c == '}' || c == '?' || c == '<' ||
			c == '>' || c == '!' || c == '@' || c == '#' ||
			c == '$' || c == '^' || c == '&' || c == ' ' ||
			c == 34 || c == 39 || c == '`' || c == '$' || c == 63)
		return (1);
	return (0);
}

char		*ft_strjoin_slash(char *s, int i)
{
	int		j;
	char	*tmp;

	if (!(tmp = (char *)malloc(ft_strlen(s) + 2)))
		return (NULL);
	j = 0;
	while (j < i)
	{
		tmp[j] = s[j];
		j++;
	}
	tmp[j++] = 92;
	while (s[i])
		tmp[j++] = s[i++];
	tmp[j] = '\0';
	ft_strdel(&s);
	return (tmp);
}

char		*check_spe_char(char *s)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (check_char(s[i]))
		{
			count++;
			s = ft_strjoin_slash(s, i);
			i++;
		}
		i++;
	}
	if (count)
		return (s);
	return (NULL);
}
