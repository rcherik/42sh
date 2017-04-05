/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 18:20:36 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 16:07:53 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "shell.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <pwd.h>

t_shell			*ft_return_shell(t_shell *shell, char *flag)
{
	static t_shell	*sin_shell = NULL;

	if (flag && ft_strequ(flag, "IS_FREE"))
		sin_shell = NULL;
	if (shell)
	{
		sin_shell = shell;
		return (NULL);
	}
	return (sin_shell);
}

static void		ft_init_intset(int *set)
{
	set[VERBOSE] = 0;
	set[PROMPT_COLOR] = 4;
	set[GLOBBING] = 1;
	set[EVENT_DES] = 1;
	set[WRITE_SET] = 1;
}

void			ft_set_shell(t_shell *shell, char ***env)
{
	char	buf[1024];

	getcwd(buf, 1024);
	shell->set_opt = (int *)malloc(sizeof(int) * 5);
	ft_init_intset(shell->set_opt);
	shell->pid = getpid();
	shell->history = NULL;
	shell->copy_buffer = NULL;
	shell->copy_comp = NULL;
	shell->env = env;
	shell->cmd = NULL;
	shell->comp = NULL;
	shell->hist_name = ft_strtjoin(buf, "/", HIST_F_NAME);
	shell->buffer = ft_strnew(BUFFER);
	shell->set_path = ft_strtjoin(buf, "/", ".set_42sh");
	shell->prompt = NULL;
	shell->prompt_len = ft_get_prompt_size(env);
	shell->cursor_pos = 0;
	shell->stop = 0;
	shell->ctrl_c = 0;
	shell->err = 0;
	shell->copied = 0;
	shell->tab = 0;
	shell->event = 0;
	shell->key = NULL;
}

void			ft_start_shell(char ***environ)
{
	t_shell			*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	ft_set_shell(shell, environ);
	shell->key = ft_strnew(3);
	ft_return_shell(shell, NULL);
	ft_get_hist_file(shell);
	ft_get_winsize(shell);
	ft_signal();
	ft_set_set(shell);
	if (begin_shell(environ))
		return ;
	ft_init_term();
	ft_put_prompt();
	while (shell->stop == 0)
	{
		read(0, shell->key, 4);
		ft_get_key(shell);
		wait_for_child();
		ft_bzero(shell->key, 4);
	}
}
