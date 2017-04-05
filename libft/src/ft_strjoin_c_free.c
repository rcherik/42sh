/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_c_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 00:27:03 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/26 01:08:32 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_c_free(char **s1, char const *s2, char c)
{
	char	*str;
	int		i;
	char	*s3;

	s3 = *s1;
	if (!(str = (char *)malloc(ft_strlen(s3) + ft_strlen(s2) + 2)))
		return (NULL);
	i = 0;
	while (*s3)
		str[i++] = *(s3++);
	while (*s2)
		str[i++] = *(s2++);
	str[i] = c;
	str[i + 1] = '\0';
	ft_strdel(s1);
	return (str);
}
