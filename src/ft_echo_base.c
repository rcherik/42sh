/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 03:36:30 by jbail             #+#    #+#             */
/*   Updated: 2014/03/27 06:48:21 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			ft_get_octal(char *s, int pos)
{
	int		i;
	int		n;
	char	*tmp;

	i = 0;
	n = 0;
	tmp = ft_strnew(3);
	while (i < 3)
	{
		if (s[pos + i] < '0' || s[pos + i] > '7')
			break ;
		tmp[i] = s[pos + i];
		i++;
	}
	i = 0;
	while (tmp[i] >= '0' && tmp[i] <= '7')
	{
		n = (n * 8) + (tmp[i] - 48);
		i++;
	}
	if (i > 0 && n < 0200)
		ft_putchar(n);
	free(tmp);
	return (2 + i);
}

static int	ft_is_hexa(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'F')
		return (2);
	if (c >= 'a' && c <= 'f')
		return (3);
	return (0);
}

static int	ft_get_n_hexa(char *s)
{
	int		i;
	int		n;
	int		diff;

	i = 0;
	n = 0;
	while ((diff = ft_is_hexa(s[i])))
	{
		if (diff == 1)
			n = (n * 16) + (s[i] - 48);
		else if (diff == 2)
			n = (n * 16) + (s[i] - 65 + 10);
		else
			n = (n * 16) + (s[i] - 97 + 10);
		i++;
	}
	return (n);
}

int			ft_get_hexa(char *s, int pos)
{
	int		i;
	int		n;
	char	*tmp;

	i = 0;
	n = 0;
	tmp = ft_strnew(2);
	while (i < 2)
	{
		if (!ft_is_hexa(s[pos + i]))
			break ;
		tmp[i] = s[pos + i];
		i++;
	}
	n = ft_get_n_hexa(tmp);
	if (i > 0 && n < 128)
		ft_putchar(n);
	free(tmp);
	return (2 + i);
}
