/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 18:51:12 by mdufaud           #+#    #+#             */
/*   Updated: 2014/02/17 21:49:18 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_color(char *color)
{
	if (ft_strcmp(color, "RED") == 0)
		ft_putstr("\033[31m");
	else if (ft_strcmp(color, "BOURG") == 0)
		ft_putstr("\033[31;01m");
	else if (ft_strcmp(color, "WHITE") == 0)
		ft_putstr("\033[37;01m");
	else if (ft_strcmp(color, "BLUE") == 0)
		ft_putstr("\033[34;01m");
	else if (ft_strcmp(color, "DARK") == 0)
		ft_putstr("\033[30;01m");
	else if (ft_strcmp(color, "PURPLE") == 0)
		ft_putstr("\033[35m");
	else if (ft_strcmp(color, "CYAN") == 0)
		ft_putstr("\033[36;01m");
	else if (ft_strcmp(color, "YELLOW") == 0)
		ft_putstr("\033[33;01m");
	else if (ft_strcmp(color, "GREEN") == 0)
		ft_putstr("\033[32m");
	else if (ft_strcmp(color, "PINK") == 0)
		ft_putstr("\033[35;01m");
}

void		ft_putcstr(char *s, char *color)
{
	ft_get_color(color);
	ft_putstr(s);
	ft_putstr("\033[00m");
}
