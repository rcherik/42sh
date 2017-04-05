/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:51:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 13:32:08 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>

int			ft_set_env(char *name, char *value, char ***env)
{
	int		i;
	char	**tmp;
	char	*search;

	i = 0;
	if (ft_strnchar(name, '='))
		return (ft_error(VAR_EQ, name) * -1);
	search = ft_strjoin(name, "=");
	while (env && *env && (*env)[i])
	{
		if (ft_strnequ((*env)[i], search, ft_strlen(search)))
		{
			ft_strdel(&(*env)[i]);
			(*env)[i] = ft_strjoin_free(&search, value);
			return (1);
		}
		i++;
	}
	if (!env)
		tmp = ft_addtab(NULL, ft_strjoin_free(&search, value));
	else
		*env = ft_addtab(*env, ft_strjoin_free(&search, value));
	if (!env)
		env = &tmp;
	return (1);
}

int			ft_unsetenv(char **args, char ***env)
{
	int		i;
	int		max;

	if (!env || !(*env)[0])
		return (ft_error(ENV_NOT_SET, "") * -1);
	i = 0;
	max = ft_tablen(*env);
	if (ft_strnchar(args[1], '='))
		ft_error(VAR_EQ, args[0]);
	else
	{
		while (i < max)
		{
			if (ft_strncmp(args[1], (*env)[i], ft_strclen((*env)[i], '=')) == 0)
			{
				*env = ft_tabdel(env, i);
				return (1);
			}
			i++;
		}
	}
	return (ft_error(ENV_NOT_FOUND, args[1]) * -1);
}

int			ft_setenv(char **args, char ***env)
{
	if (ft_tablen(args) > 3 && ft_strequ(args[0], "setenv"))
		ft_error(MUCH_ARG, args[0]);
	else if (ft_tablen(args) < 3 && ft_strequ(args[0], "setenv"))
		ft_error(LESS_ARG, args[0]);
	else if (ft_tablen(args) == 3 && ft_strequ(args[0], "setenv"))
		ft_set_env(args[1], args[2], env);
	else if (ft_tablen(args) < 2 && ft_strequ(args[0], "unsetenv"))
		ft_error(LESS_ARG, args[0]);
	else if (ft_tablen(args) > 2 && ft_strequ(args[0], "unsetenv"))
		ft_error(MUCH_ARG, args[0]);
	else if (ft_tablen(args) == 2 && ft_strequ(args[0], "unsetenv"))
		ft_unsetenv(args, env);
	else if (ft_strequ(args[0], "env"))
		ft_env(args, env);
	return (0);
}
