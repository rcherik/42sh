/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 21:21:27 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 13:39:13 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "term42.h"
#include <unistd.h>

static void		export_it(char **t, t_shell *shell, char **args)
{
	int			i;
	char		**tmp;

	i = 0;
	while (t[i])
	{
		if (!ft_strncmp(t[i], args[2], ft_strclen(t[i], '=')))
		{
			tmp = ft_strsplit(t[i], '=');
			ft_set_env(tmp[0], tmp[1], shell->env);
			ft_free_tab(&tmp);
			return ;
		}
		i++;
	}
}

static int		export_all(t_shell *shell)
{
	int		fd;
	char	*l;
	char	*tmp;
	char	*tmp2;

	if ((fd = open(shell->set_path, O_RDONLY)) == -1)
		return (-1);
	while ((get_next_line(fd, &l)) > 0)
	{
		tmp = ft_strsub(l, 0, ft_strclen(l, '='));
		tmp2 = ft_strsub(l, ft_strclen(l, '=') + 1, ft_strlen(l));
		ft_set_env(tmp, tmp2, shell->env);
		ft_strdel(&tmp);
		ft_strdel(&tmp2);
		ft_strdel(&l);
	}
	close(fd);
	return (0);
}

int				set_export(t_shell *shell, char **args)
{
	char		*tmp;
	char		**t;
	int			fd;

	if (!ft_strcmp("all", args[2]))
		return (export_all(shell));
	tmp = ft_get_env(shell->env, args[2]);
	if (tmp == NULL)
	{
		ft_add_set(shell->set_path, shell, args[2], "");
		ft_set_env(args[2], "", shell->env);
		return (0);
	}
	fd = open(shell->set_path, O_RDONLY);
	t = set_to_tab(fd);
	close(fd);
	export_it(t, shell, args);
	ft_free_tab(&t);
	ft_strdel(&tmp);
	return (0);
}
