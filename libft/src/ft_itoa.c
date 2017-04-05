/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 19:01:30 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 08:37:51 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdlib.h>

static int	ft_numsize(int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

static void	ft_fillnbr(char *s, int n)
{
	int	i;
	int	j;
	int	tmp;

	i = ft_numsize(n);
	while (i)
	{
		j = i - 1;
		tmp = n;
		while (j-- && tmp >= 10)
			tmp = tmp / 10;
		*(s) = (tmp % 10) + 48;
		i--;
		s++;
	}
	*s = '\0';
}

char		*ft_itoa(int n)
{
	char	*s;
	char	*ptr;
	int		is_neg;

	if (n < 0)
	{
		n = n * -1;
		is_neg = 1;
	}
	else
		is_neg = 0;
	s = (char *)malloc(ft_numsize(n) + 1);
	if (!s)
		return (NULL);
	ptr = s;
	if (is_neg)
		*(s++) = '-';
	ft_fillnbr(s, n);
	return (ptr);
}
