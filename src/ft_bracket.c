/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bracket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 16:02:10 by jbail             #+#    #+#             */
/*   Updated: 2014/03/24 16:02:33 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"
#include "curl.h"

int		ft_nobrak(int ret, char c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (0);
		s++;
	}
	return (ret);
}

int		ft_brak(int ret, char c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (ret);
		s++;
	}
	return (0);
}

int		ft_get_bracket_len(char *s)
{
	int		i;

	i = 0;
	if (s[0] == ']')
		i++;
	while (s[i] != ']' && ft_inhib(s, i) && s[i] != '\0')
		i++;
	return (i);
}
