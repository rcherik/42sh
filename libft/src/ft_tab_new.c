/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/07 17:32:35 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/18 20:30:01 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

char	**ft_tab_new(size_t col, size_t line)
{
	char	**tab;
	int		i;

	i = 0;
	if (!(tab = (char **)malloc(sizeof(char *) * (col + 1))))
		return (NULL);
	while (col)
	{
		if (line > 0)
			tab[i] = ft_strnew(line);
		else
			tab[i] = 0;
		i++;
		col--;
	}
	tab[i] = 0;
	return (tab);
}
