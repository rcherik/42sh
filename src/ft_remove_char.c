/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 17:50:38 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/24 23:49:12 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "curl.h"
#include "libft.h"
#include <stdlib.h>

static char	*remove(char *s, int i)
{
	char		*ret;

	ret = ft_strnew(ft_strlen(s) - 1);
	ft_strncpy(ret, s, i);
	ft_strcpy(ret + i, s + i + 1);
	ft_strdel(&s);
	return (ret);
}

char		*ft_remove_char(char *s, char c)
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c && ft_inhib(s, i))
			s = remove(s, i);
		else
			i++;
	}
	return (s);
}
