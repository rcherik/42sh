/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 20:23:29 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/25 20:51:56 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>

/*
** tabdel used for unsetenv, with focus being the env[focus] that you do not
** want in your new eden
*/

void	ft_free_lex(t_lex **lex)
{
	t_lex	*tmpfree;
	t_lex	*tmp;

	tmp = *lex;
	if (!lex || !tmp)
		return ;
	while (tmp)
	{
		if (tmp->com)
			ft_strdel(&(tmp->com));
		if (tmp->options)
			ft_strdel(&(tmp)->options);
		if (tmp->operation)
			ft_strdel(&(tmp)->operation);
		tmpfree = tmp;
		tmp = tmp->next;
		free(tmpfree);
	}
}

char	**ft_tabdel(char ***env, int focus)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	if (!env || !(*env)[0])
		return (NULL);
	ret = (char **)malloc(sizeof(char *) * ft_tablen(*env));
	while ((*env)[i])
	{
		if (i != focus)
		{
			ret[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	ret[j] = 0;
	ft_free_env(env);
	return (ret);
}

void	ft_free_env(char ***environ)
{
	char	**env;
	int		i;

	env = *environ;
	i = 0;
	while (env[i])
	{
		ft_strdel(&env[i]);
		i++;
	}
	free(env);
}
