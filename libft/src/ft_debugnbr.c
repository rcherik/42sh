/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debugnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 20:56:05 by mdufaud           #+#    #+#             */
/*   Updated: 2014/02/22 18:25:23 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_debugnbr(int n)
{
	ft_putchar_fd('\"', 2);
	ft_putnbr_fd(n, 2);
	ft_putchar_fd('\"', 2);
	ft_putchar_fd('\n', 2);
}
