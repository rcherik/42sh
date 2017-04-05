/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 02:14:02 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 06:40:15 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "term42.h"
#include "shell.h"

static int		unseting(t_shell *shell, char **args)
{
	int			fd;
	char		**t;
	int			i;

	i = 0;
	fd = open(shell->set_path, O_RDONLY);
	t = set_to_tab(fd);
	close(fd);
	fd = open(shell->set_path, O_RDWR | O_CREAT | O_TRUNC, S_IRGRP
			| S_IROTH | S_IRWXU);
	close(fd);
	fd = open(shell->set_path, O_RDWR);
	while (t[i])
	{
		if (ft_strncmp(args[1], t[i], ft_strlen(args[1])) != 0)
			ft_putendl_fd(t[i], fd);
		i++;
	}
	ft_free_tab(&t);
	close(fd);
	return (0);
}

int				ft_unset(char **args, char ***env)
{
	t_shell			*shell;
	char			*tmp;

	shell = ft_return_shell(NULL, NULL);
	if (ft_tablen(args) == 2)
	{
		tmp = ft_get_env(env, args[1]);
		if (tmp == NULL)
			return (1);
		ft_strdel(&tmp);
		return (unseting(shell, args));
	}
	return (ft_error("Unset: ", "type [help unset] to see the usage."));
}
