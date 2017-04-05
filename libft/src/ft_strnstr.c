/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 18:38:23 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/14 02:55:44 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <string.h>

static int	ft_is_str(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (n-- != 0)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
		if (s2[i] == '\0')
			return (1);
	}
	return (0);
}

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (*s2 == '\0')
		return ((char *)s1);
	if (n >= ft_strlen(s1))
		n = ft_strlen(s1);
	while (i < n)
	{
		if (*s1 == *s2)
		{
			if (ft_is_str(s1, s2, (n - i)))
				return ((char *)s1);
		}
		i++;
		s1++;
	}
	return (NULL);
}
