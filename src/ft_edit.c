/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_edit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 14:32:44 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 11:27:01 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"

void			ft_rewrite(char *s)
{
	ft_exec_termcaps("cd");
	ft_exec_termcaps("sc");
	ft_putstr(s);
	ft_exec_termcaps("rc");
}

static void		ft_jump_line(t_shell *shell)
{
	if ((shell->cursor_pos + shell->prompt_len + 1) % shell->win.col == 0)
	{
		ft_exec_termcaps("do");
		ft_exec_termcaps("ch");
	}
}

int				ft_display(t_shell *shell)
{
	char		*tmp;

	if (shell->key[0] < 32)
		return (0);
	if ((int)ft_strlen(shell->buffer) == BUFFER)
		return (0);
	if (shell->buffer[shell->cursor_pos] == '\0')
	{
		shell->buffer[shell->cursor_pos] = shell->key[0];
		ft_putchar(shell->buffer[shell->cursor_pos]);
		ft_jump_line(shell);
	}
	else
	{
		tmp = shell->buffer + shell->cursor_pos;
		ft_memmove(tmp + 1, tmp, ft_strlen(tmp));
		shell->buffer[shell->cursor_pos] = shell->key[0];
		ft_putchar(shell->buffer[shell->cursor_pos]);
		ft_jump_line(shell);
		ft_rewrite(tmp + 1);
	}
	shell->cursor_pos++;
	return (0);
}
