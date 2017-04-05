/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 13:05:29 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 04:28:47 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

/*
** Here you pipe the execution of the command and writes it in the file
** and you return the file descriptor of the said file to be used
** and duped to STDOUT for other pipes
*/

int			ft_close_fd(int fd)
{
	close(fd);
	return (0);
}

static int	ft_red_right(t_lex *lex, int ret, char *arg, char ***env)
{
	int		fd;
	char	*file;
	char	*line;

	if (!(file = ft_strdup(lex->com)))
		return (ft_error(MEM_M, NULL) * -1 + ft_close_fd(ret));
	if (ft_access_newfile(file))
		return (-1 + ft_close_fd(ret));
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRGRP | S_IROTH |
			S_IRWXU);
	free(file);
	if (fd == -1)
		return (ft_error(PERM_DENY, file) * -1 + ft_close_fd(ret));
	ret = ft_multi_pipe(ret, arg, env);
	while (get_next_line(ret, &line) > 0)
	{
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(ret);
	return (fd);
}

static int	ft_red_dright(t_lex *lex, int ret, char *arg, char ***env)
{
	int		fd;
	char	*file;
	char	*line;

	if (!(file = ft_strdup(lex->com)))
		return (ft_error(MEM_M, NULL) * -1 + ft_close_fd(ret));
	if (ft_access_newfile(file))
		return (-1 + ft_close_fd(ret));
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRGRP | S_IROTH |
			S_IRWXU);
	free(file);
	if (fd == -1)
		return (ft_error(PERM_DENY, file) * -1 + ft_close_fd(ret));
	ret = ft_multi_pipe(ret, arg, env);
	while (get_next_line(ret, &line) > 0)
	{
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(ret);
	return (fd);
}

static int	ft_red_left(t_lex *lex)
{
	int		fd;
	char	*file;
	DIR		*dir;

	if (!(file = ft_strdup(lex->com)))
		return (ft_error(MEM_M, NULL) * -1);
	if (access(file, F_OK) == -1)
	{
		free(file);
		return (ft_error(NO_FILE_DIR, file) * -1);
	}
	else if (access(file, R_OK) == -1)
	{
		free(file);
		return (ft_error(PERM_DENY, file) * -1);
	}
	else if ((dir = opendir(file)) != NULL)
	{
		closedir(dir);
		free(file);
		return (ft_error(IS_DIR, file) * -1);
	}
	fd = ft_fd_open(file);
	return (fd);
}

int			ft_manage_red(t_lex *lex, int ret, char ***env)
{
	if (ft_strequ(lex->operation, "|") && ft_strequ(lex->next->operation, ">"))
		return (ft_fd_open(ft_buildstr(lex)) + ft_close_fd(ret));
	else if (ft_strequ(lex->operation, "|")
			&& ft_strequ(lex->next->operation, ">>"))
		return (ft_fd_open(ft_buildstr(lex)) + ft_close_fd(ret));
	else if (ft_strequ(lex->operation, "|") && lex->next->com[0]
			&& ft_strequ(lex->next->operation, "<"))
		return (ft_multi_pipe(ret, ft_buildstr(lex->next), env));
	else if (ft_strequ(lex->operation, "|")
			&& ft_strequ(lex->next->operation, "<"))
		return (ft_fd_open(ft_buildstr(lex)) + ft_close_fd(ret));
	else if (ft_strequ(lex->operation, "|"))
		return (ft_multi_pipe(ret, ft_buildstr(lex), env));
	else if (ft_strequ(lex->operation, ">"))
		return (ft_red_right(lex->prev, ret, ft_buildstr(lex), env));
	else if (ft_strequ(lex->operation, ">>"))
		return (ft_red_dright(lex->prev, ret, ft_buildstr(lex), env));
	else if (ft_strequ(lex->operation, "<"))
		return (ft_red_left(lex->prev) + ft_close_fd(ret));
	return (-1);
}
