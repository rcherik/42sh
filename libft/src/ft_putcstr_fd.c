/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 19:03:31 by mdufaud           #+#    #+#             */
/*   Updated: 2014/02/17 21:49:31 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_color(int fd, char *color)
{
	if (ft_strcmp(color, "RED") == 0)
		ft_putstr_fd("\033[31m", fd);
	else if (ft_strcmp(color, "WHITE") == 0)
		ft_putstr_fd("\033[37;01m", fd);
	else if (ft_strcmp(color, "BOURG") == 0)
		ft_putstr_fd("\033[31;01m", fd);
	else if (ft_strcmp(color, "BLUE") == 0)
		ft_putstr_fd("\033[34;01m", fd);
	else if (ft_strcmp(color, "DARK") == 0)
		ft_putstr_fd("\033[30;01m", fd);
	else if (ft_strcmp(color, "PURPLE") == 0)
		ft_putstr_fd("\033[35m", fd);
	else if (ft_strcmp(color, "CYAN") == 0)
		ft_putstr_fd("\033[36;01m", fd);
	else if (ft_strcmp(color, "YELLOW") == 0)
		ft_putstr_fd("\033[33;01m", fd);
	else if (ft_strcmp(color, "GREEN") == 0)
		ft_putstr_fd("\033[32m", fd);
	else if (ft_strcmp(color, "PINK") == 0)
		ft_putstr_fd("\033[35;01m", fd);
}

void		ft_putcstr_fd(char *s, int fd, char *color)
{
	ft_get_color(fd, color);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\033[00m", fd);
}
