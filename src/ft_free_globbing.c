/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_globbing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 16:05:39 by jbail             #+#    #+#             */
/*   Updated: 2014/03/27 17:42:13 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"
#include "term42.h"
#include <stdlib.h>

void	ft_free_files(t_files *files)
{
	t_files	*tmp;

	while (files)
	{
		tmp = files;
		files = files->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

char	*ft_strjoin_and_char(char *s1, char *s2, char c)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(*tmp) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (*s1)
	{
		while (s1[j])
			tmp[i++] = s1[j++];
		if (!((i - 1 == 0) && tmp[i - 1] == '/'))
			tmp[i++] = c;
	}
	while (*s2)
		tmp[i++] = *s2++;
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_strjoin_char_free_first(char *s1, char *s2, char c)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(*tmp) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (*s1)
	{
		while (s1[j])
			tmp[i++] = s1[j++];
		if (!((i - 1 == 0) && tmp[i - 1] == '/'))
			tmp[i++] = c;
	}
	while (*s2)
		tmp[i++] = *s2++;
	tmp[i] = '\0';
	free(s1);
	return (tmp);
}

char	**ft_free_str_ret_tab(char **s)
{
	ft_strdel(s);
	return (NULL);
}
