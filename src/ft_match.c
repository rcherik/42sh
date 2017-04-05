/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 17:59:21 by jbail             #+#    #+#             */
/*   Updated: 2014/03/14 02:42:54 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

int		ft_match(char *s1, char *s2)
{
	int		add;

	add = 0;
	if (*s1 && *s2 && *s1 == '\\' && *(s1 + 1) == *s2)
		return (ft_match(s1 + 2, s2 + 1));
	if (*s1 == '[' && (add = ft_check_brackets(s1 + 1, *s2)))
		return (ft_match(s1 + add, s2 + 1));
	if (*s1 && *s2 && *s1 == '*' && *s2 == '*')
		return (ft_match(s1, s2 + 1));
	if (*s1 && *s2 && (*s1 == *s2 || *s1 == '?'))
		return (ft_match(s1 + 1, s2 + 1));
	if (*s1 && *s2 && *s1 == '*')
		return (ft_match(s1 + 1, s2) + ft_match(s1, s2 + 1));
	if (*s1 == '*' && *s2 == '\0')
		return (ft_match(s1 + 1, s2));
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}

int		ft_first_match(char *s1, char *s2)
{
	int		add;

	add = 0;
	if (*s1 == '[' && *s2 != '.' && (add = ft_check_brackets(s1 + 1, *s2)))
		return (ft_match(s1 + add, s2 + 1));
	if (*s1 && *s2 && *s1 == '*' && *s2 == '*')
		return (ft_match(s1, s2 + 1));
	if (*s1 && *s2 && *s1 == '?' && *s2 != '.')
		return (ft_match(s1 + 1, s2 + 1));
	if (*s1 && *s2 && *s1 == *s2)
		return (ft_match(s1 + 1, s2 + 1));
	if (*s1 && *s2 && *s2 != '.' && *s1 == '*')
		return (ft_match(s1 + 1, s2) + ft_match(s1, s2 + 1));
	if (*s1 == '*' && *s2 == '\0')
		return (ft_match(s1 + 1, s2));
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}
