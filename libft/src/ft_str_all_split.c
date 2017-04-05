/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_all_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/16 15:34:32 by jbail             #+#    #+#             */
/*   Updated: 2014/03/16 15:34:33 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_count_all(const char *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == c))
			count++;
		i++;
	}
	return (count + 1);
}

static void	ft_fill_tab(char **tab, int splits, char *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	if (s[0] == c)
	{
		tab[0] = ft_strnew(1);
		k++;
		i++;
	}
	while (k < splits)
	{
		j = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i])
			s[i++] = '\0';
		tab[k] = ft_strdup(s + j);
		k++;
	}
	tab[k] = NULL;
}

char		**ft_str_all_split(char const *str, char c)
{
	char	**tab;
	int		splits;
	char	*s;

	s = ft_strdup(str);
	splits = ft_count_all(s, c);
	if (!(tab = (char **)malloc(sizeof(char *) * (splits + 1))))
		return (NULL);
	ft_fill_tab(tab, splits, s, c);
	free(s);
	return (tab);
}
