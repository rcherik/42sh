/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 15:35:54 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 04:30:30 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"

void		ft_home(t_shell *shell)
{
	int			l;

	(void)shell;
	l = (shell->cursor_pos + shell->prompt_len) / shell->win.col;
	if (shell->cursor_pos > 0)
	{
		while (l)
		{
			ft_exec_termcaps("up");
			l--;
		}
		tputs(tgoto(tgetstr("ch", NULL), 0, shell->prompt_len), 1, ft_puts);
	}
	shell->cursor_pos = 0;
}

void		ft_home2(t_shell *shell)
{
	int			l;

	(void)shell;
	l = (shell->cursor_pos + shell->prompt_len) / shell->win.col;
	if (shell->cursor_pos >= 0)
	{
		while (l)
		{
			ft_exec_termcaps("up");
			l--;
		}
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_puts);
	}
	shell->cursor_pos = 0;
}

void		ft_end(t_shell *shell)
{
	int		c[3];

	ft_init_tabint(c, 3);
	ft_home(shell);
	c[2] = (int)ft_strlen(shell->buffer);
	c[0] = (c[2] + shell->prompt_len - 1) / shell->win.col;
	c[1] = (c[2] + shell->prompt_len - 1) % shell->win.col;
	if (shell->cursor_pos < (int)(ft_strlen(shell->buffer)))
	{
		while (c[0])
		{
			ft_exec_termcaps("do");
			c[0] -= 1;
		}
		tputs(tgoto(tgetstr("ch", NULL), 0, c[1] + 1), 1, ft_puts);
	}
	shell->cursor_pos = c[2];
}
