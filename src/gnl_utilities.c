/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 23:01:27 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/26 06:31:32 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_line	*gnl_free(t_line **tab_free, char **free_str)
{
	if (*free_str)
		ft_strdel(free_str);
	if (tab_free && *tab_free)
	{
		free(*tab_free);
		*tab_free = NULL;
	}
	return (NULL);
}

void	gnl_reset_read_add(t_line **tab)
{
	char	*tmp;

	tmp = (*tab)->string;
	(*tab)->string = ft_strsub((*tab)->string, (*tab)->i, (*tab)->size);
	(*tab)->size = (*tab)->size - (*tab)->i;
	(*tab)->i = 0;
	free(tmp);
}
