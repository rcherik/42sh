/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 12:41:31 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/14 02:57:56 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strtrim(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s || !s[0])
		return (NULL);
	while (s[i] && ft_isspace(s[i]))
		i++;
	j = i;
	while (s[j + 1])
		j++;
	while (j >= 0 && ft_isspace(s[j]))
		j--;
	return (ft_strsub(s, i, j + 1));
}
