/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_curl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 19:19:13 by jbail             #+#    #+#             */
/*   Updated: 2014/03/16 15:22:17 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "curl.h"
#include "shell.h"

char	**ft_add_tab_curl(char **t1, char **t2, int len)
{
	int		i;
	int		j;
	char	**tmp;

	tmp = (char **)malloc(sizeof(*tmp) * (ft_tlen(t1) + ft_tlen(t2)));
	i = 0;
	j = 0;
	while (t1 && i < len)
	{
		tmp[i] = ft_strdup(t1[i]);
		free(t1[i]);
		i++;
	}
	while (t2[j])
		tmp[i++] = t2[j++];
	j = len + 1;
	while (t1[j])
	{
		tmp[i] = ft_strdup(t1[j]);
		free(t1[j++]);
		i++;
	}
	tmp[i] = NULL;
	free(t1);
	return (tmp);
}

char	*ft_in_curl(char *s, int i)
{
	int		len;
	char	*str;

	len = 0;
	while (s[i + len] != '}')
		len++;
	str = ft_strsub_len(s, i, len);
	return (str);
}

char	**ft_add_to_curl(char **tab, char *s, int *pos)
{
	int		i;
	int		j;
	int		k;
	char	**tmp;
	char	**tmp2;

	tmp = ft_str_all_split(s, ',');
	*pos += ft_strlen(s) + 1;
	tmp2 = (char **)malloc(sizeof(char *) * (ft_count_commas(tab, s) + 1));
	i = 0;
	j = 0;
	while (tab[i])
	{
		k = 0;
		while (tmp[k])
			tmp2[j++] = ft_strjoin(tab[i], tmp[k++]);
		i++;
	}
	tmp2[j] = NULL;
	free(s);
	ft_free_tabcpy(tab);
	ft_free_tabcpy(tmp);
	return (tmp2);
}

char	**ft_get_curl(char **tab, char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '{' && !(i > 0 && s[i - 1] == '\\'))
		{
			if (ft_correct_curl(s, i))
				tab = ft_add_to_curl(tab, ft_in_curl(s, i + 1), &i);
			else
				tab = ft_add_c_to_tab(tab, s[i]);
		}
		else
			tab = ft_add_c_to_tab(tab, s[i]);
		i++;
	}
	i = 0;
	free(s);
	return (tab);
}

char	**ft_start_curl(char *s, int *len)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * 2);
	tab[0] = ft_strnew(1);
	tab[1] = NULL;
	if (ft_count_curl(s))
		tab = ft_get_curl(tab, s);
	else
	{
		free(tab[0]);
		tab[0] = s;
	}
	*len += ft_tlen(tab);
	return (tab);
}
