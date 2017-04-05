/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 12:48:02 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/23 22:36:52 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "term42.h"

int		clear_all_hist(t_shell *shell)
{
	int	code;

	code = 1;
	free_history(&shell->history);
	shell->history = NULL;
	code = clear_file();
	return (code);
}

int		ft_history_error(char *err, char *s, char ***env)
{
	(void)env;
	ft_putcstr_fd("history: ", 2, "WHITE");
	ft_putcstr_fd(err, 2, "RED");
	ft_putendl_fd(ft_sub(s, 0, ft_strlen(s)), 2);
	return (-1);
}

int		ft_remove_hist(t_hist *hist, char **args)
{
	int		num;

	if (!ft_strdigit(args[0]))
		return (ft_error("history -d: put a valid number: ", args[0]));
	num = ft_atoi(args[0]);
	return (remove_history(hist, num));
}

int		ft_history(char **args, char ***env)
{
	t_shell	*shell;
	int		code;

	shell = ft_return_shell(NULL, NULL);
	code = 1;
	if (!args[1])
		code = list_history(shell->history);
	else if (ft_strequ(args[1], "-d") && ft_tablen(args) < 4)
		code = ft_remove_hist(shell->history, args + 2);
	else if (ft_tablen(args) > 2 || (args[1] && !ft_strnchar(args[1], '-')))
		code = ft_print_error("Type \"help\" to see how to use history") * -1;
	else if (ft_strequ(args[1], "-c"))
		code = free_history(&shell->history);
	else if (ft_strequ(args[1], "-w"))
		code = hist_to_file(shell->history);
	else if (ft_strequ(args[1], "-C"))
		code = clear_file();
	else if (ft_strequ(args[1], "-l"))
		code = list_file();
	else if (ft_strequ(args[1], "-Cc") || ft_strequ(args[1], "-cC"))
		code = clear_all_hist(shell);
	else if (ft_strnchar(args[1], '-') == 1)
		return (ft_history_error(ILL_OP, args[1], env));
	return (code);
}
