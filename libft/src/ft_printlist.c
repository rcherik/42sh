/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 14:56:06 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/12 23:08:03 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_printlist(int *list, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		ft_putnbr(list[i]);
		write(1, " ", 1);
		i++;
	}
}
