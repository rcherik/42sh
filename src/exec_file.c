/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 00:23:48 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 17:53:14 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "shell.h"
#include "term42.h"
#include "error_code.h"
#include <unistd.h>

int			ft_process_file(char *s, char ***env)
{
	int	child;
	int	stat_loc;

	if (!(child = fork()) == -1)
		return (ft_error(MEM_F, NULL) * -2);
	if (child == 0)
		_exit(ft_cmd_interpretor(s, env));
	else
		waitpid(child, &stat_loc, 0);
	return (ft_status_interpretor(stat_loc));
}

int			exec_file(char *s, char ***env)
{
	int		fd;
	char	*line;
	int		ret;
	t_shell	*shell;

	ret = 0;
	line = NULL;
	if ((fd = open(s, O_RDONLY)) == -1)
		return (ft_error(NO_FILE_DIR, s));
	shell = ft_emulate_shell(env);
	while (get_next_line(fd, &line) > 0)
	{
		ret = ft_process_file(line, env);
		if (ret == -2)
			break ;
	}
	ft_free_shell(shell);
	_exit(ret);
}
