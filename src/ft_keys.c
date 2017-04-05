/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 15:25:37 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 06:54:04 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "shell.h"

void		ft_back_del(t_shell *shell)
{
	char	*tmp;

	if (shell->cursor_pos > 0)
	{
		ft_left(shell);
		tmp = shell->buffer + shell->cursor_pos;
		ft_memmove(tmp, tmp + 1, ft_strlen(tmp) + 1);
		ft_exec_termcaps("dc");
		ft_rewrite(tmp);
	}
}

void		ft_del(t_shell *shell)
{
	char		*tmp;

	if (shell->cursor_pos < (int)ft_strlen(shell->buffer))
	{
		tmp = shell->buffer + shell->cursor_pos;
		ft_memmove(tmp, tmp + 1, ft_strlen(tmp) + 1);
		ft_rewrite(tmp);
	}
}

static int	reset(t_shell *shell)
{
	ft_putchar('\n');
	shell->copied = 0;
	shell->cursor_pos = 0;
	ft_bzero(shell->buffer, BUFFER + 1);
	ft_put_prompt();
	return (1);
}

void		ft_return(t_shell *shell)
{
	if (shell->set_opt[VERBOSE] == 1)
	{
		ft_putchar('\n');
		ft_putstr(shell->buffer);
	}
	shell->event = 0;
	shell->err = get_events(shell);
	if (shell->err < 0 && reset(shell))
		return ;
	shell->cmd = ft_strdup(shell->buffer);
	if (shell->history)
		last_history(&shell->history);
	if (ft_strcmp(shell->buffer, ""))
		add_history(&shell->history, shell);
	ft_putchar('\n');
	shell->copied = 0;
	shell->cursor_pos = 0;
	if (ft_cmd_interpretor(shell->cmd, shell->env) != 130)
		ft_put_prompt();
	wait_for_child();
	ft_bzero(shell->buffer, BUFFER + 1);
}
