/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 17:33:53 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 01:51:01 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"

void		ft_alt_left(t_shell *shell)
{
	int			l;

	l = (shell->cursor_pos + shell->prompt_len) / shell->win.col;
	if (shell->cursor_pos && shell->buffer[shell->cursor_pos - 1] == ' ')
	{
		shell->cursor_pos--;
		while (shell->cursor_pos && shell->buffer[shell->cursor_pos] == ' ')
			shell->cursor_pos--;
	}
	while (shell->cursor_pos && shell->buffer[shell->cursor_pos] != ' ')
		shell->cursor_pos--;
	shell->cursor_pos = shell->cursor_pos ? shell->cursor_pos + 1 :
		shell->cursor_pos;
	l -= (shell->cursor_pos + shell->prompt_len) / shell->win.col;
	while (l--)
		ft_exec_termcaps("up");
	tputs(tgoto(tgetstr("ch", NULL), 0, (shell->cursor_pos + shell->prompt_len)
				% shell->win.col), 1, ft_puts);
}

void		ft_alt_right(t_shell *shell)
{
	int			start;
	int			l;
	char		*next;

	start = (shell->cursor_pos + shell->prompt_len) / shell->win.col;
	next = ft_strchr(&shell->buffer[shell->cursor_pos], ' ');
	if (!next)
		return ;
	while (*next && *next == ' ')
		next++;
	if (!next)
		return ;
	shell->cursor_pos = (int)ft_strlen(shell->buffer) - (int)ft_strlen(next);
	l = ((shell->cursor_pos + shell->prompt_len) / shell->win.col) - start;
	while (l--)
		ft_exec_termcaps("do");
	tputs(tgoto(tgetstr("ch", NULL), 0, (shell->cursor_pos + shell->prompt_len)
				% shell->win.col), 1, ft_puts);
}

void		ft_alt_down(t_shell *shell)
{
	int		n;
	int		np;

	n = (int)ft_strlen(shell->buffer);
	np = shell->cursor_pos + shell->win.col;
	if (np <= n)
	{
		shell->cursor_pos = np;
		ft_exec_termcaps("do");
		tputs(tgoto(tgetstr("ch", NULL), 0, (shell->cursor_pos +
					shell->prompt_len) % shell->win.col), 1, ft_puts);
	}
}

void		ft_alt_up(t_shell *shell)
{
	if (shell->cursor_pos > shell->win.col - shell->prompt_len - 1)
	{
		shell->cursor_pos -= shell->win.col;
		ft_exec_termcaps("up");
		if (shell->cursor_pos < 0)
		{
			shell->cursor_pos = 0;
			tputs(tgoto(tgetstr("ch", NULL), 0, shell->prompt_len), 1, ft_puts);
		}
	}
}
