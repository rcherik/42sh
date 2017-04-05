/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/08 13:05:29 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 05:55:50 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

/*
** Put the result of the reading end pipe in a file, TRUNCs it so all that was
** is none, or creates it with drwxr--r--
*/

int			ft_ctfd(int fd1, int fd2, int fd3)
{
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}

static int	ft_last_red_left(t_lex *lex, int ret, char ***env)
{
	char	*line;

	if (ret == -1)
		return (ret);
	if (!lex->com[0])
	{
		close(ret);
		if (!(line = ft_buildstr(lex->prev)))
			return (ft_error(MEM_M, NULL) * -1);
		if ((ret = ft_fd_open(line)) == -1)
			return (-1);
		while (get_next_line(ret, &line) > 0)
		{
			ft_putendl_fd(line, 1);
			free(line);
		}
	}
	else
		return (ft_final_pipe(ret, ft_buildstr(lex), env));
	close(ret);
	return (0);
}

int			ft_manage_final_red(t_lex *lex, int ret, char ***env)
{
	int		tmp;

	tmp = ret;
	if (ft_strequ(lex->next->operation, "<"))
		return (ft_last_red_left(lex->next, ret, env));
	else if (ft_strequ(lex->next->operation, "|"))
		return (ft_final_pipe(ret, ft_buildstr(lex), env));
	close(ret);
	return (tmp);
}
