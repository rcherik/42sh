/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 18:31:16 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 06:42:10 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "curl.h"
#include <unistd.h>

static int	ft_print_ret(char c, int ret)
{
	write(1, &c, 1);
	return (ret);
}

static int	ft_print_special(char *s, int i)
{
	if (!s[i + 1])
		return (ft_print_ret('\\', 1));
	if (s[i + 1] && s[i + 1] == 'n')
		return (ft_print_ret('\n', 2));
	if (s[i + 1] && s[i + 1] == 'v')
		return (ft_print_ret('\v', 2));
	if (s[i + 1] && s[i + 1] == 't')
		return (ft_print_ret('\t', 2));
	if (s[i + 1] && s[i + 1] == 'r')
		return (ft_print_ret('\r', 2));
	if (s[i + 1] && s[i + 1] == 'c')
		return (-1);
	if (s[i + 1] && s[i + 1] == '\\')
		return (ft_print_ret('\\', 2));
	if (s[i + 1] && s[i + 1] == 'b')
		return (ft_print_ret('\b', 2));
	if (s[i + 1] && s[i + 1] == '0')
		return (ft_get_octal(s, i + 2));
	if (s[i + 1] && s[i + 1] == 'x')
		return (ft_get_hexa(s, i + 2));
	return (1);
}

static void	ft_echo_str(char *s, int *flags)
{
	int		i;
	int		z;

	i = 0;
	while (s[i])
	{
		z = 1;
		if (s[i] == '\\' && (ft_inhib(s, i) || i == 0))
			z = ft_print_special(s, i);
		else
			write(1, s + i, 1);
		if (z == -1 && (*flags = z))
			return ;
		i += z;
	}
}

static int	ft_get_echo_flags(char *s)
{
	if (!s)
		return (0);
	if (ft_strequ(s, "-n"))
		return (1);
	else if (ft_strequ(s, "-E"))
		return (2);
	else if (ft_strequ(s, "-nE") || ft_strequ(s, "-En"))
		return (3);
	return (0);
}

int			ft_builtin_echo(char **tab, char ***env)
{
	int		flags;
	int		i;

	(void)env;
	flags = ft_get_echo_flags(tab[1]);
	i = flags ? 2 : 1;
	while (tab[i])
	{
		if (flags & 2)
			ft_putstr(tab[i]);
		else
			ft_echo_str(tab[i], &flags);
		if (tab[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!(flags & 1) && flags != -1)
		write(1, "\n", 1);
	return (0);
}
