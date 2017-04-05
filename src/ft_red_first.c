/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 13:05:29 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 05:55:40 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

/*
** Protected way to open a file, all errors taken charge of
*/

int			ft_fd_open(char *file)
{
	int	fd;
	DIR	*direct;

	if (access(file, F_OK) == -1)
		return (ft_error(NO_FILE_DIR, file) * -1);
	else if (access(file, R_OK) == -1)
		return (ft_error(PERM_DENY, file) * -1);
	else if ((direct = opendir(file)) != NULL)
	{
		closedir(direct);
		return (ft_error(IS_DIR, file) * -1);
	}
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_error(PERM_DENY, file) * -1);
	free(file);
	return (fd);
}

static int	ft_first_red_left(t_lex *lex)
{
	char	*file;
	int		fd;

	if (!(file = ft_buildstr(lex)))
		return (ft_error(MEM_M, NULL) * -1);
	fd = ft_fd_open(file);
	return (fd);
}

static int	ft_first_red_right(t_lex *lex, char *arg, char ***env)
{
	int		fd;
	int		ret;
	char	*file;
	char	*line;

	if (!(file = ft_strdup(lex->com)))
		return (ft_error(MEM_M, NULL) * -1);
	if (ft_access_newfile(file))
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRGRP | S_IROTH |
			S_IRWXU);
	free(file);
	if (fd == -1)
		return (ft_print_error_free(PERM_DENY, arg) * -1);
	ret = ft_first_pipe(arg, env);
	while (get_next_line(ret, &line) > 0)
	{
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(ret);
	return (fd);
}

static int	ft_first_red_dright(t_lex *lex, char *arg, char ***env)
{
	int		fd;
	int		ret;
	char	*file;
	char	*line;

	if (!(file = ft_strdup(lex->com)))
		return (ft_error(MEM_M, NULL) * -1);
	if (ft_access_newfile(file))
		return (-1);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRGRP | S_IROTH |
			S_IRWXU);
	free(file);
	if (fd == -1)
		return (ft_print_error_free(PERM_DENY, arg) * -1);
	ret = ft_first_pipe(arg, env);
	while (get_next_line(ret, &line) > 0)
	{
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(ret);
	return (fd);
}

int			ft_manage_first_red(t_lex *lex, char ***env)
{
	if (ft_strequ(lex->operation, "|"))
		return (ft_first_pipe(ft_buildstr(lex), env));
	else if (ft_strequ(lex->operation, ">>"))
		return (ft_first_red_dright(lex->prev, ft_buildstr(lex), env));
	else if (ft_strequ(lex->operation, ">"))
		return (ft_first_red_right(lex->prev, ft_buildstr(lex), env));
	else if (ft_strequ(lex->operation, "<"))
		return (ft_first_red_left(lex->prev));
	return (-1);
}
