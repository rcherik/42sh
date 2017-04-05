/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/17 14:21:14 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/17 14:27:43 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int		ft_error2(char *err, char *s)
{
	ft_putcstr_fd("\n42sh: ", 2, "WHITE");
	ft_putcstr_fd(err, 2, "RED");
	if (s)
		ft_putstr_fd(s, 2);
	return (1);
}
