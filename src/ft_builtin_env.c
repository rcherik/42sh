/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 19:19:27 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 18:49:28 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include <stdlib.h>

/*
** If no -i, will print env, else, execute the next cmd without env
** Can bear in order of if :
** env -i STR=str cmd
** env -i cmd
** env cmd
** env
*/

static int		ft_env_i(char **args)
{
	char	*tmp;
	char	**tmpenv;
	int		ret;

	tmpenv = NULL;
	if (args[1] && args[2] && ft_strequ(args[1], "-i")
			&& ft_strnchar(args[2], '='))
	{
		tmp = ft_strsub(args[2], 0, ft_strclen(args[2], '='));
		if (ft_set_env(tmp, (args[2] + ft_strclen(args[2], '=') + 1),
					&tmpenv) < 0)
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
		ret = ft_check_builtin(ft_ret_builtins(), args + 3, &tmpenv);
		ft_free_tab(&tmpenv);
		return (ret);
	}
	else if (args[1] && ft_strequ(args[1], "-i"))
		return (ft_check_builtin(ft_ret_builtins(), args + 2, NULL));
	return (0);
}

int				ft_print_env(char ***environ)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!environ)
		return (ft_error(ENV_NOT_SET, NULL) * -1);
	while ((*environ)[i])
	{
		ft_putendl((*environ)[i]);
		count++;
		i++;
	}
	if (!count)
		return (1);
	return (0);
}

static int		ft_env_one_arg(char **args, char ***environ)
{
	char	**env;
	char	**tmpenv;
	int		ret;
	char	*tmp;

	ret = 0;
	tmpenv = NULL;
	env = (!environ) ? NULL : *environ;
	if (args[1] && ft_strnchar(args[1], '='))
	{
		tmp = ft_strsub(args[1], 0, ft_strclen(args[1], '='));
		tmpenv = ft_tabdup(env);
		if (ft_set_env(tmp, (args[1] + ft_strclen(args[1], '=') + 1),
					&tmpenv) < 0)
		{
			ft_free_tab(&tmpenv);
			free(tmp);
			return (-1);
		}
		ret = ft_check_builtin(ft_ret_builtins(), args + 2, &tmpenv);
		ft_free_tab(&tmpenv);
		return (ret);
	}
	return (0);
}

int				ft_env(char **args, char ***environ)
{
	int		ret;

	ret = 1;
	if ((ret = ft_env_i(args)) < 0)
		return (-1);
	if (ret && (ret = ft_env_one_arg(args, environ)) < 0)
		return (-1);
	if (ret && args[1] && environ && !args[2])
		ret = ft_check_builtin(ft_ret_builtins(), args + 1, environ);
	if (ret && args[1] && !environ && !args[2])
		ret = ft_check_builtin(ft_ret_builtins(), args + 1, NULL);
	if (args[1] && !args[2])
		ft_check_builtin(ft_ret_builtins(), args + 1, environ);
	if (!args[1])
		ret = ft_print_env(environ);
	return (ret);
}
