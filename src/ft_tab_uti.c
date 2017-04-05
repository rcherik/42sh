/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_uti.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 13:33:26 by jbail             #+#    #+#             */
/*   Updated: 2014/03/18 21:08:48 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"
#include "curl.h"

char	**ft_add_tab(char **tab1, char **tab2)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	tmp = (char **)malloc(sizeof(*tmp) * (ft_tlen(tab1) + ft_tlen(tab2) + 1));
	if (tab1)
	{
		while (tab1[i])
		{
			tmp[i] = tab1[i];
			i++;
		}
		free(tab1);
	}
	j = 0;
	if (tab2)
	{
		while (tab2[j])
			tmp[i++] = tab2[j++];
	}
	tmp[i] = NULL;
	return (tmp);
}

void	ft_free_tabcpy(char **tab)
{
	int		i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}
