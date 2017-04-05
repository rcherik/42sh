/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 17:59:32 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 18:04:57 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include <sys/ioctl.h>
#include <unistd.h>

void		ft_exit_term(void)
{
	struct termios		term;
	int					fd;

	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1)
		fd = 0;
	tcgetattr(fd, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &term);
	if (fd > 0)
		close(fd);
}

void		ft_init_term(void)
{
	struct termios		term;
	int					fd;

	fd = open("/dev/tty", O_RDONLY);
	if (fd == -1)
		fd = 0;
	tcgetattr(fd, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(fd, TCSANOW, &term);
	if (fd > 0)
		close(fd);
}

void		ft_get_winsize(t_shell *shell)
{
	struct winsize	term_size;
	int				fd;

	fd = open("/dev/tty", O_RDONLY);
	if (fd < 0)
		fd = 0;
	ioctl(fd, TIOCGWINSZ, &term_size);
	shell->win.col = term_size.ws_col;
	shell->win.line = term_size.ws_row;
	if (fd != 0)
		close(fd);
}

int			is_in_term(void)
{
	struct termios		term;

	tcgetattr(0, &term);
	if (!(term.c_lflag & (ICANON | ECHO)))
		return (1);
	return (0);
}
