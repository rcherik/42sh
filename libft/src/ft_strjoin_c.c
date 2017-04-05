/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 18:44:31 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 08:43:50 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_c(char const *s1, char const *s2, char c)
{
	char	*str;
	int		i;

	if (!s1)
		s1 = ft_strnew(1);
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	i = 0;
	if (str == NULL)
		return (NULL);
	while (*s1)
		str[i++] = *(s1++);
	while (*s2)
		str[i++] = *(s2++);
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}
