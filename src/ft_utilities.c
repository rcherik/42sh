/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 02:08:49 by jbail             #+#    #+#             */
/*   Updated: 2014/03/25 21:41:48 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "curl.h"

int		ft_tlen(char **tab)
{
	int		i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	*ft_add_c_to_str(char *s, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(ft_strlen(s) + 2);
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i++] = c;
	tmp[i] = '\0';
	return (tmp);
}

char	**ft_add_c_to_tab(char **tab, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		tmp = ft_add_c_to_str(tab[i], c);
		free(tab[i]);
		tab[i] = tmp;
		i++;
	}
	return (tab);
}

char	*ft_strjoin_n_free_first(char *s, char *s2)
{
	int		i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(*tmp) * (ft_strlen(s) + ft_strlen(s2) + 2));
	i = 0;
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	if (i > 0)
		tmp[i++] = ' ';
	while (*s2)
		tmp[i++] = *s2++;
	tmp[i] = '\0';
	free(s);
	return (tmp);
}

int		ft_inhib(char *s, int pos)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (pos - i >= 0 && s[pos - i] == '\\')
	{
		i++;
		count++;
	}
	if (count % 2 == 1)
		return (0);
	return (1);
}
