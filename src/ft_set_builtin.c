/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 21:51:42 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 16:21:28 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term42.h"
#include "shell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int		list_set(t_shell *shell)
{
	int			fd;
	char		*l;

	if ((fd = open(shell->set_path, O_RDONLY)) < 1)
	{
		ft_putendl("Can't find .set_42sh");
		return (-1);
	}
	while (get_next_line(fd, &l) > 0)
	{
		ft_putendl(l);
		ft_strdel(&l);
	}
	close(fd);
	return (0);
}

char			**set_to_tab(int fd)
{
	char		*l;
	char		*tmp;
	char		**ret;

	tmp = ft_strnew(1);
	while (get_next_line(fd, &l) > 0)
	{
		tmp = ft_strjoin_c_free(&tmp, l, '\n');
		ft_strdel(&l);
	}
	ret = ft_strsplit(tmp, '\n');
	ft_strdel(&tmp);
	return (ret);
}

int				ft_set_builtin(char **args, char ***env)
{
	t_shell		*shell;

	(void)env;
	shell = ft_return_shell(NULL, NULL);
	if (!args[1])
		list_set(shell);
	else if (ft_tablen(args) == 2)
	{
		if (!ft_set_builtin2(args, shell))
			return (-1);
	}
	else if (ft_tablen(args) == 3)
	{
		if (ft_strequ(args[1], "-e"))
			set_export(shell, args);
		else if (ft_strequ(args[1], "-c") && ft_atoi(args[2]) > 0)
			ft_set_prompt(shell, args[2]);
		else
			ft_add_set(shell->set_path, shell, args[1], args[2]);
	}
	else
		return (ft_error("Set: ", "type [help set] to see the usage."));
	return (0);
}
