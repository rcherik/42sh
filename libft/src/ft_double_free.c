/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 21:13:07 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/25 21:14:00 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"

void		ft_double_free(char *s1, char *s2)
{
	ft_strdel(&s1);
	ft_strdel(&s2);
}
