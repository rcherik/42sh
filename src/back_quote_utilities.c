/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_quote_utilities.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 19:00:30 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/26 00:15:55 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "term42.h"
#include "libft.h"

char	*ft_str_space_join(char *s1, char *s2)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	tmp = s1;
	if (!(ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2)))
		return (NULL);
	while (s1 && *s1)
		ret[i++] = *(s1++);
	if (*tmp && *s2)
		ret[i++] = ' ';
	while (s2 && *s2)
		ret[i++] = *(s2++);
	ret[i] = 0;
	if (tmp)
		ft_strdel(&tmp);
	return (ret);
}

int		check_c(char *s, int i)
{
	if (s[i + 1] && (s[i + 1] == '\\' || s[i + 1] == '$'
					|| s[i + 1] == '\"' || s[i + 1] == '`'))
		return (0);
	return (1);
}
