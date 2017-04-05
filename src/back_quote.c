/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 15:29:46 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 00:32:06 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "shell.h"
#include "term42.h"
#include <unistd.h>

static void	lexer_return_interpretor(char *s, char ***env)
{
	int	ret;

	ret = 0;
	ret = ft_cmd_interpretor(s, env);
	_exit(ret);
}

static int	check_bq_count(int count, int node)
{
	t_shell		*shell;
	static int	buffer_len = 0;

	shell = ft_return_shell(NULL, NULL);
	if (node == 1)
	{
		if (shell)
			buffer_len = ft_strlen(shell->buffer);
	}
	if (node == 2)
		buffer_len = 0;
	if (!node && shell && ((buffer_len + count) >= BUFFER))
		return (1);
	return (0);
}

static void	fill_str(char **s, int pipex, char *free_str)
{
	char	*line;
	int		count;
	int		err;

	count = 0;
	err = 0;
	ft_strdel(&free_str);
	check_bq_count(0, 1);
	while (get_next_line(pipex, &line) > 0)
	{
		if (!err)
		{
			*s = ft_str_space_join(*s, line);
			count += ft_strlen(*s);
			err = check_bq_count(count, 0);
		}
		ft_strdel(&line);
	}
	check_bq_count(0, 2);
	if ((s && *s && !**s) || err)
		ft_strdel(s);
}

static int	ft_duo_fd_close(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
	return (1);
}

char		*exec_back_quote(char *s, char ***env)
{
	int		father;
	int		ret[2];
	char	*str;
	int		err;

	str = ft_strnew(0);
	if ((err = pipe(ret)) == -1)
		ft_error(MEM_P, NULL);
	if (err >= 0 && (father = fork()) == -1)
		ft_error(MEM_F, NULL);
	if ((err < 0 || father < 0) && ft_duo_fd_close(ret[0], ret[1]))
		return (NULL);
	if (father == 0)
	{
		dup2(ret[1], 1);
		lexer_return_interpretor(s, env);
	}
	else
	{
		close(ret[1]);
		fill_str(&str, ret[0], s);
		close(ret[0]);
	}
	return (str);
}
