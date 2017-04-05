/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_builtin2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 21:51:42 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 07:34:34 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term42.h"
#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int		verbose(t_shell *shell)
{
	int			fd;
	char		*tmp;

	fd = open(shell->set_path, O_RDWR, O_CREAT, O_APPEND,
			S_IRGRP | S_IROTH | S_IRWXU);
	if ((tmp = ft_get_env(shell->env, "VERBOSE")) == NULL)
	{
		shell->set_opt[VERBOSE] = 1;
		write(fd, "VERBOSE=1\n", 10);
		close(fd);
		return (0);
	}
	if (ft_atoi(tmp) < 1)
	{
		ft_add_set(shell->set_path, shell, "VERBOSE", "1");
		shell->set_opt[VERBOSE] = 1;
	}
	else
	{
		ft_add_set(shell->set_path, shell, "VERBOSE", "0");
		shell->set_opt[VERBOSE] = 0;
	}
	ft_strdel(&tmp);
	close(fd);
	return (0);
}

static int		set_globbing(t_shell *shell)
{
	char		*tmp;

	tmp = NULL;
	tmp = ft_get_env(shell->env, "GLOBBING");
	if (!tmp || ft_atoi(tmp) == 0)
		ft_add_set(shell->set_path, shell, "GLOBBING", "1");
	else
		ft_add_set(shell->set_path, shell, "GLOBBING", "0");
	free(tmp);
	return (0);
}

int				ft_set_builtin2(char **args, t_shell *shell)
{
	if (ft_strequ(args[1], "-v"))
		verbose(shell);
	else if (ft_strequ(args[1], "-g"))
		set_globbing(shell);
	else if (ft_strequ(args[1], "-d"))
		set_event(shell);
	else
		return (ft_error("Set: ", "type [help set] to see the usage."));
	return (1);
}
