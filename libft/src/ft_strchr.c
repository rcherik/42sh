/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 14:47:13 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/14 02:53:22 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char	f;

	f = (char)c;
	while (*s)
	{
		if (*s == f)
			return ((char *)s);
		s++;
	}
	if (*s == f)
		return ((char *)s);
	else
		return (NULL);
}
