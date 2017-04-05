/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 15:06:43 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/14 02:58:18 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_tabdup(char **tab)
{
	char	**ret;
	int		i;

	i = 0;
	ret = NULL;
	if (!(ret = (char **)malloc(sizeof(char *) * ft_tablen(tab) + 1)))
		return (NULL);
	while (tab[i])
	{
		if (!(ret[i] = ft_strdup(tab[i])))
			return (NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
