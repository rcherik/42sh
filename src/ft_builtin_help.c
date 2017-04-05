/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 18:36:22 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 06:01:10 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term42.h"

static int	ft_general_help(void)
{
	ft_putstr("These shell commands are defined internally, type");
	ft_putendltab(" `help name` to find out more about the function `name`.");
	ft_putendltab("env [-i] [name=[value]] [cmd]");
	ft_putendltab("setenv [name] [value]");
	ft_putendltab("unsetenv [name]");
	ft_putendltab("cd [- | dir]");
	ft_putendltab("echo [-n] [args ...]");
	ft_putendltab("history [-c | -d [n] | -w | -C | -l]");
	ft_putendltab("type [cmd]");
	ft_putendltab("unset [entry] | [all]");
	ft_putendltab("set [name] | -c [color_code] | -v | -e [entry] | -g | -d]");
	ft_putendl("exit [code]");
	return (0);
}

static int	ft_help_builtin(int node)
{
	if (node == 0)
		ft_putstr("Change directory if specified, else, go to $HOME. Type '-'");
	if (node == 0)
		ft_putendl(" to get to the $OLDPWD directory\n\tcd [- | dir]");
	if (node == 1)
	{
		ft_putendltab("History: List your cmd history, type -c to clear it.");
		ft_putendltab("-d [n] to delete the entry at position n.");
		ft_putendltab("-w to write out the current history the history file.");
		ft_putendltab("-C to clear to history file, -l to display it.");
		ft_putendltab("!! refer to the previous command.");
		ft_putendltab("!n refer to command line n.");
		ft_putendltab("!-n refer to the command n line back.");
		ft_putendltab("!# repeat the entire command typed so far.");
		ft_putendl("history [-c | -d [n] | -w | -C | -l]");
	}
	if (node == 2)
	{
		ft_putstr("Type shows the path to `cmd`");
		ft_putendltab(" or precise if it's a builtin.");
		ft_putendl("type [cmd]");
	}
	return (0);
}

static int	ft_env_help(int node)
{
	if (!node)
	{
		ft_putendl("Env display your actual environment.");
		ft_putstr("Type -i to execute the next cmd without NULL env,");
		ft_putstr(" you can ");
		ft_putstr("however precise before the cmd an environment variable");
		ft_putendltab(" which will be used to the cmd execution.");
		ft_putendl("env [-i] [name=[value]] [cmd].");
	}
	if (node == 1)
	{
		ft_putstr("Setenv change your actual environment by remplacing or");
		ft_putstr("adding `name`. Make sure the `name` do not possess an '='");
		ft_putendl(" in it.\n\tsetenv [name] [value]");
	}
	if (node == 2)
		ft_putstr("Unsetenv unset your acutal environment. Removing the");
	if (node == 2)
		ft_putendl(" `name` variable\n\tunsetenv [name]");
	return (0);
}

int			ft_builtin_help(char **args, char ***env)
{
	if (ft_tablen(args) > 2)
	{
		ft_putendl("usage : help [builtin]");
		return (-1);
	}
	if (!args[1])
		return (ft_general_help());
	if (ft_strequ(args[1], "cd"))
		return (ft_help_builtin(0));
	if (ft_strequ(args[1], "history"))
		return (ft_help_builtin(1));
	if (ft_strequ(args[1], "type"))
		return (ft_help_builtin(2));
	if (ft_strequ(args[1], "env"))
		return (ft_env_help(0));
	if (ft_strequ(args[1], "setenv"))
		return (ft_env_help(1));
	if (ft_strequ(args[1], "unsetenv"))
		return (ft_env_help(2));
	if (ft_strequ(args[1], "unset"))
		return (ft_unset_help());
	if (ft_strequ(args[1], "set"))
		return (ft_set_help());
	(void)env;
	return (0);
}
