/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 18:03:44 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 02:49:31 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_check_builtins_type(char *s, t_built *builtins)
{
	int	i;

	i = 0;
	while (i < BUILTIN_NUM)
	{
		if (ft_strequ(s, builtins[i].cmd))
			return (s);
		i++;
	}
	return (NULL);
}

static char	*ft_check_type(char *s, char ***env)
{
	char	**all;
	char	*path;
	char	*com;

	all = NULL;
	if ((path = ft_get_env(env, "PATH")))
	{
		all = ft_strsplit(path, ':');
		ft_strdel(&path);
	}
	if (!(com = ft_check_builtins_type(s, ft_ret_builtins())))
	{
		if (all)
		{
			com = ft_check_all(s, all);
			ft_free_tab(&all);
		}
		return (com);
	}
	if (all)
		ft_free_tab(&all);
	return ("IS_BUILTIN");
}

int			ft_builtin_type(char **args, char ***env)
{
	char	*ret;
	int		i;

	i = 1;
	while (args[i])
	{
		if (!(ret = ft_check_type(args[i], env)))
		{
			ft_putendl(ft_strcat(args[i], " not found"));
			i++;
			continue ;
		}
		ft_putstr(args[i]);
		ft_putstr(" is ");
		if (ft_strequ(ret, "IS_BUILTIN"))
			ft_putendl("a builtin");
		else if (ret)
		{
			ft_putendl(ret);
			ft_strdel(&ret);
		}
		i++;
	}
	return (0);
}
