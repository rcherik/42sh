/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tabint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 20:37:59 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/25 20:43:21 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"

void		ft_init_tabint(int *t, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		t[i] = 0;
		i++;
	}
}