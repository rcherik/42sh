/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transf_red.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 23:38:51 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 08:55:14 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "term42.h"
#include <stdlib.h>

static int	ft_return_new(char *s)
{
	(void)s;
	s = ft_strnew(0);
	return (1);
}

static int	ft_metamorph_file(t_lex *lex)
{
	t_shell	*shell;
	char	**tab;

	shell = ft_return_shell(NULL, NULL);
	lex->com = ft_quotes(lex->com, shell->env);
	if (!lex->com)
		return (ft_return_new(lex->com));
	tab = ft_quotesplit(lex->com, *shell->env);
	tab = ft_transform(tab);
	if (!tab)
		return (1);
	if (ft_tablen(tab) > 1)
	{
		ft_free_tab(&tab);
		lex->com = ft_strnew(0);
		return (ft_error(AMBIGOUS, NULL));
	}
	else
		lex->com = tab[0];
	free(tab);
	return (0);
}

int			ft_transf_red(t_lex *lex)
{
	int	err;

	err = 0;
	while (lex->next)
		lex = lex->next;
	while (lex && !err)
	{
		if (lex && ft_isred(lex, "<>"))
			err = ft_metamorph_file(lex->prev);
		lex = lex->prev;
	}
	return (err);
}
