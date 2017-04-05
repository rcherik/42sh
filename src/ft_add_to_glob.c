/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_glob.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 13:24:40 by jbail             #+#    #+#             */
/*   Updated: 2014/03/23 20:01:58 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"
#include "curl.h"
#include <stdlib.h>

char	**ft_add_to_opts(char **tab, char *opt)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (ft_tlen(tab) + 2));
	if (tab)
	{
		while (tab[i])
		{
			tmp[i] = tab[i];
			i++;
		}
	}
	tmp[i++] = ft_strdup(opt);
	tmp[i] = NULL;
	free(tab);
	return (tmp);
}

t_files	*ft_add_to_list(t_files *list, char *s)
{
	t_files	*tmp;
	t_files	*tmp2;

	tmp2 = list;
	tmp = (t_files *)malloc(sizeof(*tmp));
	tmp->file = ft_strdup(s);
	tmp->next = NULL;
	if (list == NULL)
		return (tmp);
	while (tmp2->next)
		tmp2 = tmp2->next;
	tmp2->next = tmp;
	return (list);
}

char	*ft_add_c_to_string(char c, char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)malloc(sizeof(*tmp) * (ft_strlen(s) + 2));
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	tmp[i++] = c;
	tmp[i] = '\0';
	free(s);
	return (tmp);
}

char	*ft_add_to_string(char c, char c2, char *s)
{
	int		i;
	char	*tmp;

	if (c > c2)
		return (s);
	tmp = (char *)malloc(sizeof(*tmp) * ((ft_strlen(s) + (c2 - c + 2))));
	i = 0;
	while (s[i])
	{
		tmp[i] = s[i];
		i++;
	}
	while (c <= c2)
	{
		if (c != '/')
			tmp[i++] = c++;
		else
			c++;
	}
	tmp[i] = '\0';
	free(s);
	return (tmp);
}
