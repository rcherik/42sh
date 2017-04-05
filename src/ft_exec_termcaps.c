/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_termcaps.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 14:48:19 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 11:24:33 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "shell.h"
#include <unistd.h>

int		begin_shell(char ***env)
{
	char	*term;
	char	buffer[2048];

	term = ft_get_env(env, "TERM");
	if ((tgetent(buffer, term) < 1))
		return (ft_error(ENV_NOT_FOUND, "TERM"));
	ft_strdel(&term);
	ft_init_term();
	ft_exec_termcaps("cl");
	return (0);
}

int		ft_puts(int c)
{
	ft_putchar(c);
	return (1);
}

int		ft_exec_termcaps(char *s)
{
	tputs(tgoto(tgetstr((s), NULL), 0, 0), 1, &ft_puts);
	return (0);
}
