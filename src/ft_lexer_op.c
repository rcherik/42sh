/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 21:31:41 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/25 21:04:23 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdlib.h>

/*
** ft_isred check the operation part of a lexem to check if it sticks to the
** grammar you sent via *gram
*/

int		ft_isred(t_lex *lex, char const *gram)
{
	int	i;

	i = 0;
	if (!lex)
		return (0);
	while (gram[i])
	{
		if (lex->operation[0] == gram[i] && !lex->operation[1])
			return (1);
		if (lex->operation[1] && lex->operation[1] == gram[i]
				&& lex->operation[0] == gram[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_buildstr(t_lex *lex)
{
	if (!lex)
		return (NULL);
	if (!lex->options[0])
		return (ft_strdup(lex->com));
	else
		return (ft_strtjoin(lex->com, " ", lex->options));
}

t_lex	*ft_init_lex(void)
{
	t_lex	*lex;

	lex = (t_lex *)malloc(sizeof(t_lex));
	lex->com = NULL;
	lex->options = NULL;
	lex->operation = NULL;
	lex->next = NULL;
	lex->prev = NULL;
	return (lex);
}

t_lex	*ft_add_lex(t_lex *old, t_lex *new)
{
	if (!old)
	{
		new->next = old;
		old = new;
	}
	else
	{
		old->prev = new;
		new->next = old;
		old = new;
	}
	return (old);
}

void	ft_print_lexer(t_lex *lex)
{
	if (!lex)
		ft_debugstr("UH OH, NO LEXER");
	while (lex->next)
		lex = lex->next;
	ft_putendl_fd("----------PRINTING LEXEM------------", 2);
	while (lex)
	{
		if (lex->com)
			ft_debugs("lex->com : ", lex->com);
		if (lex->options)
			ft_debugs("lex->options : ", lex->options);
		if (lex->operation)
			ft_debugs("lex->operation : ", lex->operation);
		if (lex->prev)
			ft_putendl_fd("----------NEXT LEXEM------------", 2);
		lex = lex->prev;
	}
	ft_putendl_fd("----------END OF LEXEM------------", 2);
}
