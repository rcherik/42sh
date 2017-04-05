/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 20:02:26 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 11:19:19 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "term42.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

static void	ft_close_process(void)
{
	t_shell		*shell;

	shell = ft_return_shell(NULL, NULL);
	ft_end(shell);
	ft_bzero(shell->buffer, BUFFER + 1);
	shell->cursor_pos = 0;
	while (shell->history && shell->history->prev)
		shell->history = shell->history->prev;
	if (shell->pid == getpid())
		ft_putchar('\n');
	if (shell->pid == getpid())
	{
		ft_init_term();
		ft_put_prompt();
	}
}

static void	ft_update_winsize(void)
{
	int				fd;
	t_shell			*shell;
	struct winsize	term_size;

	shell = ft_return_shell(NULL, NULL);
	ft_exec_termcaps("cl");
	ft_put_prompt();
	fd = open("/dev/tty", O_RDONLY);
	ioctl(fd, TIOCGWINSZ, &term_size);
	shell->win.line = term_size.ws_row;
	shell->win.col = term_size.ws_col;
	close(fd);
	ft_bzero(shell->buffer, BUFFER + 1);
	shell->cursor_pos = 0;
}

static void	ft_sig_exit(int sig)
{
	ft_exit_term();
	_exit(sig + 128);
}

static void	ft_signal_handler(int sig)
{
	if (sig == SIGHUP)
		ft_sig_exit(sig);
	if (sig == SIGABRT)
		ft_sig_exit(sig);
	if (sig == SIGINT)
		ft_close_process();
	if (sig == SIGCONT)
	{
		ft_init_term();
		ft_put_prompt();
	}
	if (sig == SIGWINCH)
		ft_update_winsize();
}

void		ft_signal(void)
{
	signal(SIGCHLD, ft_signal_handler);
	signal(SIGHUP, ft_signal_handler);
	signal(SIGWINCH, ft_signal_handler);
	signal(SIGABRT, ft_signal_handler);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_signal_handler);
	signal(SIGCONT, ft_signal_handler);
}
