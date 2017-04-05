/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 20:26:55 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 17:53:03 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "get_next_line.h"
#include "term42.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int			ft_exec_atty(char *s, char ***env)
{
	int	child;
	int	stat_loc;
	int	ret;

	ret = 0;
	if (!(child = fork()) == -1)
		return (ft_error(MEM_F, NULL) * -2);
	if (child == 0)
	{
		ret = ft_cmd_interpretor(s, env);
		_exit(ret);
	}
	else
		waitpid(child, &stat_loc, 0);
	return (ft_status_interpretor(stat_loc));
}

t_shell		*ft_emulate_shell(char ***env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	ft_set_shell(shell, env);
	ft_return_shell(shell, NULL);
	ft_signal();
	ft_set_set(shell);
	return (shell);
}

void		ft_atty(char ***env)
{
	char	*line;
	int		ret;
	t_shell	*shell;

	ret = 0;
	line = NULL;
	shell = ft_emulate_shell(env);
	while (get_next_line(0, &line) > 0)
	{
		ret = ft_exec_atty(line, env);
		if (ret == -2)
			break ;
	}
	ft_free_shell(shell);
	_exit(ret);
}
