/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 13:32:55 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 17:52:48 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

static int	ft_cd_old(char ***env)
{
	char	*buf;

	if (!(buf = (char *)malloc(1024)))
		return (ft_print_error("malloc error") * -1);
	getcwd(buf, 1024);
	if (!buf)
		return (ft_error("cwd path too long", NULL) * -1);
	ft_set_env("OLDPWD", buf, env);
	ft_strdel(&buf);
	return (0);
}

static int	ft_cd_env(char ***env, char *where)
{
	char	*tmp;
	char	*get_env;

	tmp = NULL;
	if (ft_strequ(where, "OLDPWD"))
		tmp = ft_get_env(env, "PWD");
	else
		ft_cd_old(env);
	if (!(get_env = ft_get_env(env, where)))
	{
		ft_strdel(&tmp);
		return (ft_error(ENV_NOT_FOUND, where) * -1);
	}
	if ((chdir(get_env)) == -1)
	{
		ft_strdel(&tmp);
		return (ft_print_error_free("cwd path too long", get_env) * -1);
	}
	ft_set_env("PWD", get_env, env);
	ft_set_env("OLDPWD", tmp, env);
	ft_putendl(get_env);
	free(get_env);
	free(tmp);
	return (0);
}

static int	ft_cd_to_home(char ***env)
{
	char	*home;
	char	*buf;

	if (!(home = ft_get_env(env, "HOME")))
		return (ft_error(ENV_NOT_FOUND, "HOME") * -1);
	if (ft_single_access(home, "IS_DIR"))
		return (ft_print_error_free(NULL, home));
	if (!(buf = (char *)malloc(1024)))
	{
		free(home);
		return (ft_error(MEM_M, NULL) * -1);
	}
	ft_cd_old(env);
	if ((chdir(home)) == -1)
	{
		free(buf);
		return (ft_print_error_free("path too long", home) * -1);
	}
	free(home);
	if (!getcwd(buf, 1024))
		return (ft_print_error_free("cwd path too long", buf) * -1);
	ft_set_env("PWD", buf, env);
	free(buf);
	return (0);
}

int			ft_cd(char **args, char ***env)
{
	char	*buf;

	if (!args[1])
		return (ft_cd_to_home(env));
	else if (ft_tablen(args) > 2)
		return (ft_error(MUCH_ARG, args[0]));
	else if (args[1][0] == '-' && !args[1][1])
		ft_cd_env(env, "OLDPWD");
	else if (args[1])
	{
		if (!(buf = (char *)malloc(1024)))
			return (ft_error(MEM_M, NULL) * -1);
		if (ft_single_access(args[1], "IS_DIR"))
			return (ft_print_error_free(NULL, buf));
		ft_cd_old(env);
		if ((chdir(args[1])) == -1)
			return (ft_print_error_free("path too long", buf) * -1);
		if (!getcwd(buf, 1024))
			return (ft_print_error_free("cwd path too long", buf) * -1);
		ft_set_env("PWD", buf, env);
		free(buf);
	}
	return (0);
}
