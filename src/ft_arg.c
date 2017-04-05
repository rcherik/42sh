/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:40:37 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 18:17:07 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "globbing.h"
#include "term42.h"
#include "error_code.h"
#include <stdlib.h>
#include <unistd.h>

char		*ft_check_all(char *s, char **all)
{
	int		i;
	char	*tmp;

	i = 0;
	while (all[i])
	{
		tmp = ft_strtjoin(all[i], "/", s);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		ft_strdel(&tmp);
		i++;
	}
	return (NULL);
}

static int	ft_path_check(char **s, char ***env)
{
	char	**all;
	char	*com;
	char	*path;
	int		err;

	if (!(path = ft_get_env(env, "PATH")))
		return (ft_error(ENV_NOT_FOUND, "PATH") * -1);
	all = ft_strsplit(path, ':');
	ft_strdel(&path);
	if (!(com = ft_check_all(s[0], all)))
	{
		ft_free_tab(&all);
		return (ft_alternate_path_check(s, env));
	}
	ft_free_tab(&all);
	err = ft_exec(s, env, com);
	update_last_cmd(err);
	free(com);
	return (err);
}

int			ft_check_builtin(t_built *built, char **args, char ***env)
{
	int	i;

	i = 0;
	if (!args || !args[0])
		return (-1);
	if (args[0][0] == '.' || args[0][0] == '/')
		return (ft_exec_path(args, env));
	while (i < BUILTIN_NUM)
	{
		if (ft_strequ(args[0], built[i].cmd))
			return (built[i].f(args, env));
		i++;
	}
	return (ft_path_check(args, env));
}

char		**ft_transform(char **tab)
{
	char	**free_tab;
	char	**ret;
	int		i;

	if (!tab)
		return (NULL);
	i = 0;
	ret = NULL;
	tab = ft_init_transform(tab);
	while (tab[i])
	{
		if ((free_tab = ft_start_globbing(tab[i])) == NULL)
		{
			ft_free_tabcpy(ret);
			free(tab);
			return (free_tab);
		}
		ret = ft_add_tab(ret, free_tab);
		free(free_tab);
		i++;
	}
	free(tab);
	return (ret);
}

int			ft_arg(char *s, char ***environ)
{
	char	**args;
	int		ret;
	char	**env;

	if (!*s)
		return (-1);
	if (s[0] && s[0] == '(')
		return (sub_shell(s, environ));
	env = (!environ) ? NULL : *environ;
	s = ft_quotes(s, environ);
	args = ft_quotesplit(s, env);
	args = ft_transform(args);
	if (!args || (args && ft_check_args_length(args)))
		return (-1);
	ret = ft_check_builtin(ft_ret_builtins(), args, environ);
	ft_free_tab(&args);
	return (ret);
}
