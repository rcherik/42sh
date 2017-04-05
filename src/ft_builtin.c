/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/19 20:49:15 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 04:20:12 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "term42.h"
#include <unistd.h>
#include <stdlib.h>
#include "error_code.h"

static const t_built	g_builtins[] = {

	{
		"set", &ft_set_builtin
	},
	{
		"unset", &ft_unset
	},
	{
		"env", &ft_setenv
	},
	{
		"setenv", &ft_setenv
	},
	{
		"unsetenv", &ft_setenv
	},
	{
		"cd", &ft_cd
	},
	{
		"echo", &ft_builtin_echo
	},
	{
		"help", &ft_builtin_help
	},
	{
		"history", &ft_history
	},
	{
		"type", &ft_builtin_type
	},
	{
		"exit", &ft_exit
	}
};

t_built			*ft_ret_builtins(void)
{
	t_built	*ret;

	ret = (t_built *)g_builtins;
	return (ret);
}

int				ft_exit(char **args, char ***env)
{
	t_shell	*shell;
	int		ex;

	(void)env;
	shell = ft_return_shell(NULL, NULL);
	if (ft_tablen(args) > 2)
		return (ft_error(MUCH_ARG, args[0]) * -1);
	ft_free_shell(shell);
	if (args[1])
	{
		ex = ft_atoi(args[1]);
		_exit(ex);
	}
	else
		_exit(0);
	return (-1);
}
