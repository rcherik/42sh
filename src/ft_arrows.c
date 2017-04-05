/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrows.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 16:21:57 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 10:18:15 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include <stdlib.h>

void	ft_right(t_shell *shell)
{
	if (shell->cursor_pos < (int)ft_strlen(shell->buffer))
	{
		shell->cursor_pos++;
		if ((shell->cursor_pos + shell->prompt_len) % shell->win.col == 0)
		{
			ft_exec_termcaps("do");
			ft_exec_termcaps("ch");
		}
		else
			ft_exec_termcaps("nd");
	}
}

void	ft_left(t_shell *shell)
{
	int		tmp;

	if (shell->cursor_pos > 0)
	{
		tmp = (shell->cursor_pos + shell->prompt_len) >= shell->win.col ?
			shell->prompt_len : 0;
		if ((shell->cursor_pos + tmp) % shell->win.col == 0)
		{
			ft_exec_termcaps("up");
			tputs(tgoto(tgetstr("ch", NULL), 0, shell->win.col - 1),
					1, ft_puts);
		}
		else
			tputs(tgoto(tgetstr("le", NULL), 0, 0), 1, ft_puts);
		shell->cursor_pos -= 1;
	}
}

void	ft_down(t_shell *shell)
{
	char		*ret;

	if (!(shell->history))
		return ;
	ret = browse_history(&shell->history, shell, 'd');
	if (ret)
	{
		ft_home2(shell);
		ft_exec_termcaps("cd");
		ft_memset(shell->buffer, '\0', BUFFER + 1);
		ft_memcpy(shell->buffer, ret, ft_strlen(ret) + 1);
		shell->cursor_pos = ft_strlen(shell->buffer);
		ft_put_prompt();
		ft_putstr(shell->buffer);
	}
	if (!shell->copied)
		ft_strdel(&(shell->copy_buffer));
}

void	ft_up(t_shell *shell)
{
	char	*ret;
	char	*tmp;

	if (!(shell->history))
		return ;
	tmp = ft_strdup(shell->buffer);
	ft_free_comp(&shell);
	if (!shell->copied)
	{
		ft_strdel(&shell->copy_buffer);
		shell->copy_buffer = ft_strdup(shell->buffer);
		shell->copied = 1;
	}
	ret = browse_history(&shell->history, shell, 'u');
	if (ret && ft_strcmp(ret, tmp))
	{
		ft_home2(shell);
		ft_exec_termcaps("cd");
		ft_bzero(shell->buffer, BUFFER + 1);
		ft_memcpy(shell->buffer, ret, ft_strlen(ret) + 1);
		ft_put_prompt();
		shell->cursor_pos = ft_strlen(shell->buffer);
		ft_putstr(shell->buffer);
	}
	free(tmp);
}
