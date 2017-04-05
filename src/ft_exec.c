/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 20:50:27 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 14:31:40 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "term42.h"
#include <stdlib.h>
#include <unistd.h>

/*
** ft_exec_path execute an arg of this sort : ./42sh or /bin/ls -la
** ft_exec receive the place of the executable binary in char *place (/bin/ls)
** with s[0] == "ls" ; s[1] == "-l" ; s[2] == "-a" or s[1] == "-la"
*/

int		ft_status_interpretor(int stat_loc)
{
	if (WIFSTOPPED(stat_loc) && isatty(0))
		ft_init_term();
	if (WIFSIGNALED(stat_loc))
		return (ft_signal_interpretor(WTERMSIG(stat_loc) + 128));
	if (WIFEXITED(stat_loc))
		return (WEXITSTATUS(stat_loc));
	return (stat_loc);
}

int		ft_exec_path(char **args, char ***environ)
{
	pid_t	child;
	int		stat_loc;
	char	**env;

	stat_loc = 0;
	env = !environ ? NULL : *environ;
	if (access(args[0], F_OK) == -1)
		return (ft_error(NO_FILE_DIR, args[0]) * -1);
	if ((child = fork()) == -1)
		return (ft_error(MEM_F, NULL) * -1);
	if (child == 0)
	{
		execve(args[0], args, env);
		ft_error(PERM_DENY, args[0]);
		_exit(126);
	}
	else
		waitpid(child, &stat_loc, 0);
	return (ft_status_interpretor(stat_loc));
}

int		ft_exec(char **s, char ***environ, char *place)
{
	pid_t	child;
	int		stat_loc;
	char	**env;

	stat_loc = 0;
	env = !environ ? NULL : *environ;
	if ((child = fork()) == -1)
		return (ft_error(MEM_F, NULL) * -1);
	if (child == 0)
	{
		execve(place, s, env);
		ft_error(PERM_DENY, place);
		_exit(126);
	}
	else
		waitpid(child, &stat_loc, 0);
	return (ft_status_interpretor(stat_loc));
}
