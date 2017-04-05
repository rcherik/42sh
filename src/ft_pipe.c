/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 00:23:24 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/26 07:15:34 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "term42.h"
#include <unistd.h>
#include <stdlib.h>

static void	ft_cmd_ret(char *arg, char ***env)
{
	int	ret;

	ret = 1;
	ret = ft_arg(arg, env);
	_exit(ret);
}

int			ft_final_pipe(int pipex, char *arg, char ***env)
{
	pid_t	father;
	int		stat_loc;

	stat_loc = 0;
	if ((father = fork()) == -1)
		return (ft_error(MEM_F, NULL) * -2 + ft_close_fd(pipex));
	if (father > 0)
		waitpid(father, &stat_loc, 0);
	else
	{
		dup2(pipex, 0);
		close(pipex);
		ft_cmd_ret(arg, env);
	}
	ft_strdel(&arg);
	close(pipex);
	return (ft_status_interpretor(stat_loc));
}

int			ft_multi_pipe(int pipex, char *arg, char ***env)
{
	int		ret[2];
	pid_t	father;
	int		stat_loc;

	if (pipe(ret) == -1)
		return (ft_error(MEM_P, NULL) * -2 + ft_close_fd(pipex));
	if ((father = fork()) == -1)
		return (ft_error(MEM_F, NULL) * -2 + ft_ctfd(pipex, ret[0], ret[1]));
	if (father)
	{
		waitpid(father, &stat_loc, WNOHANG);
		close(pipex);
		close(ret[1]);
		ft_strdel(&arg);
		return (ret[0]);
	}
	else
	{
		dup2(pipex, 0);
		close(pipex);
		dup2(ret[1], 1);
		_exit(ft_arg(arg, env));
	}
	return (0);
}

int			ft_first_pipe(char *arg, char ***env)
{
	int			ret[2];
	pid_t		father;
	int			stat_loc;

	if (pipe(ret) == -1)
		return (ft_error(MEM_P, NULL) * -2);
	if ((father = fork()) == -1)
		return (ft_error(MEM_F, NULL) * -2 + ft_close_fd(ret[0]) +
		ft_close_fd(ret[1]));
	if (father)
	{
		waitpid(father, &stat_loc, WNOHANG);
		close(ret[1]);
		ft_strdel(&arg);
		return (ret[0]);
	}
	else
	{
		dup2(ret[1], 1);
		_exit(ft_arg(arg, env));
	}
	return (0);
}
