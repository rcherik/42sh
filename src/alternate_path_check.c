/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alternate_path_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 22:28:07 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 09:12:10 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "term42.h"
#include <stdlib.h>

int			ft_alternate_path_check(char **s, char ***env)
{
	char	**all;
	char	*com;
	char	*path;
	int		err;

	if (!(path = ft_get_set(ft_strdup("PATH"))))
	{
		if (!(path = ft_get_env(env, "PATH")))
			return (ft_error(ENV_NOT_FOUND, "PATH") * -1);
	}
	all = ft_strsplit(path, ':');
	ft_strdel(&path);
	if (!(com = ft_check_all(s[0], all)))
	{
		ft_free_tab(&all);
		return (ft_error(COM_NOT_FOUND, s[0]) + 126);
	}
	ft_free_tab(&all);
	err = ft_exec(s, env, com);
	free(com);
	return (err);
}
