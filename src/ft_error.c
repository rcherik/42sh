/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:46:26 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/25 20:47:19 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

/*
** ft_error print error code macro located in error_code.h
** ft_print_error print a personalised error string
** ft_print_error_exit ...
** ft_single_access check :
** - The existence of the file, if not "no such file or directory"
** - If i asked for a dir, and it is not opendirable, then "not a dir"
** - Can i execute it ? Else "permission deny"
** - If i asked for a file, and it is opendirable then "is a dir"
*/

int		ft_error(char *err, char *s)
{
	ft_putcstr_fd("42sh: ", 2, "WHITE");
	ft_putcstr_fd(err, 2, "RED");
	if (s)
		ft_putendl_fd(s, 2);
	else
		ft_putchar('\n');
	return (1);
}

int		ft_print_error(char *s)
{
	ft_putendl_fd(s, 2);
	return (1);
}

int		ft_print_error_free(char *err, char *s)
{
	if (!err)
	{
		free(s);
		return (-1);
	}
	ft_error(err, s);
	free(s);
	return (1);
}

int		ft_single_access(char *arg, char *is)
{
	DIR	*dir;

	dir = NULL;
	if (access(arg, F_OK) == -1)
		return (ft_error(NO_FILE_DIR, arg));
	if (is && ft_strequ(is, "IS_DIR") && (dir = opendir(arg)) == NULL)
		return (ft_error(NOT_DIR, arg));
	if (dir)
		closedir(dir);
	if (access(arg, X_OK) == -1)
		return (ft_error(PERM_DENY, arg));
	if (is && ft_strequ(is, "IS_FILE") && (dir = opendir(arg)) != NULL)
	{
		closedir(dir);
		return (ft_error(IS_DIR, arg));
	}
	return (0);
}

int		ft_access_newfile(char *arg)
{
	DIR	*dir;

	dir = NULL;
	if (access(arg, F_OK) == -1)
		return (0);
	if ((dir = opendir(arg)) != NULL)
	{
		free(arg);
		closedir(dir);
		return (ft_error(IS_DIR, arg));
	}
	if (access(arg, W_OK) == -1)
	{
		free(arg);
		return (ft_error(PERM_DENY, arg));
	}
	return (0);
}
