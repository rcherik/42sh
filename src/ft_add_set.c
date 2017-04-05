/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 22:43:44 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 13:05:12 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term42.h"
#include <unistd.h>
#include <fcntl.h>
#include "shell.h"

int			ft_set_prompt(t_shell *shell, char *c)
{
	char		*tmp;

	tmp = ft_get_env(shell->env, "PROMPT_COLOR");
	if (tmp == NULL)
	{
		ft_add_set(shell->set_path, shell, "PROMPT_COLOR", "4");
		shell->set_opt[PROMPT_COLOR] = 4;
		return (0);
	}
	ft_add_set(shell->set_path, shell, "PROMPT_COLOR", c);
	shell->set_opt[PROMPT_COLOR] = ft_atoi(c);
	ft_strdel(&tmp);
	return (0);
}

int			set_event(t_shell *shell)
{
	char		*tmp;

	tmp = ft_get_env(shell->env, "EVENT_DES");
	if (tmp == NULL)
	{
		ft_add_set(shell->set_path, shell, "EVENT_DES", "1");
		shell->set_opt[EVENT_DES] = 1;
		return (0);
	}
	else if (ft_atoi(tmp) == 0)
	{
		ft_add_set(shell->set_path, shell, "EVENT_DES", "1");
		shell->set_opt[EVENT_DES] = 1;
	}
	else if (ft_atoi(tmp) == 1)
	{
		ft_add_set(shell->set_path, shell, "EVENT_DES", "0");
		shell->set_opt[EVENT_DES] = 0;
	}
	ft_strdel(&tmp);
	return (0);
}

static void	write_in_file(char *path, char **t)
{
	int			fd;
	int			i;

	i = 0;
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRGRP | S_IROTH | S_IRWXU);
	close(fd);
	fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRGRP | S_IROTH | S_IRWXU);
	while (t[i])
	{
		ft_putendl_fd(t[i], fd);
		i++;
	}
	close(fd);
}

static void	ft_add_set2(char **t, char *s1, char *s2, int fd)
{
	ft_free_tab(&t);
	ft_putstr_fd(s1, fd);
	ft_putchar_fd('=', fd);
	ft_putendl_fd(s2, fd);
	close(fd);
}

void		ft_add_set(char *path, t_shell *shell, char *s1, char *s2)
{
	int		i;
	int		fd;
	char	**t;

	(void)shell;
	fd = open(path, O_RDWR | O_CREAT, S_IRGRP | S_IROTH | S_IRWXU);
	i = 0;
	t = set_to_tab(fd);
	while (t[i])
	{
		if (!ft_strncmp(t[i], s1, ft_strclen(t[i], '=')))
		{
			ft_strdel(&t[i]);
			t[i] = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
			ft_strncpy(t[i], s1, ft_strlen(s1));
			t[i][ft_strlen(s1)] = '=';
			t[i] = ft_strjoin_free(&t[i], s2);
			write_in_file(path, t);
			ft_free_tab(&t);
			close(fd);
			return ;
		}
		i++;
	}
	ft_add_set2(t, s1, s2, fd);
}
