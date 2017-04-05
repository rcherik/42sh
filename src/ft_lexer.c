/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/23 18:40:50 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 15:31:38 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "curl.h"
#include <stdlib.h>

/*
** The lexer is built this way :
** lexer->com : contains the cmd
** lexer->options : contains the options
** lexer-> operation : contains the operation
** For this str : ls | ls -la ; wc -c < auteur
** Lexer will be :
** Lex->com : "ls" / lex->options : "" / lex->operation "|"
** Lex->com : "ls" / lex->options : "-la" / lex->operation ";"
** Lex->com : "wc" / lex->options : "-c" / lex->operation "<"
** Lex->com : "auteur" / lex->options : "" / lex->operation ""
** Period
** To use it properly please be aware of the direction :
** For this str : ls | ls -la ; wc -c < auteur
** Begin at : auteur;
** Direction : <- Next;
** Direction : -> Prev;
*/

static char		*ft_fill_com(char *s, int *i)
{
	int		j;
	char	*ret;

	while (ft_isspace(s[*i]) && ft_inhib(s, *i))
		*i += 1;
	if (!s || !s[*i] || (ft_isop(s[*i], "<>;|&") && ft_inhib(s, *i)))
		return (ft_strnew(1));
	if (s[*i + 1] && ft_isop(s[*i + 1], "<>;|&") && ft_inhib(s, *i))
		return (ft_strnew(1));
	j = *i;
	while (s[j] && !(ft_isspace(s[j]) && ft_inhib(s, j)))
	{
		if (ft_isop(s[j], "\"'`({[") && ft_inhib(s, j))
			ft_loop_gram(s, &j);
		j++;
	}
	ret = ft_strsub(s, *i, j);
	*i = j;
	return (ret);
}

static char		*ft_fill_options(char *s, int *i)
{
	int		j;
	char	*ret;

	while (s[*i] && ft_isspace(s[*i]) && ft_inhib(s, *i))
		*i += 1;
	if (!s || !s[*i] || (ft_isop(s[*i], "<>;|&") && ft_inhib(s, *i)))
		return (ft_strnew(1));
	if (s[*i + 1] && ft_isop(s[*i + 1], "<>;|&") && ft_inhib(s, *i))
		return (ft_strnew(1));
	j = *i;
	while (s[j] && !(ft_isop(s[j], "<>;|&") && ft_inhib(s, j)))
	{
		if (ft_isop(s[j], "\"'`({[") && ft_inhib(s, j))
			ft_loop_gram(s, &j);
		j++;
	}
	ret = ft_strsub(s, *i, j);
	*i = j;
	return (ret);
}

static char		*ft_fill_operation(char *s, int *i)
{
	int		j;
	char	*ret;

	if (!s || !s[*i])
		return (ft_strnew(1));
	if (ft_isspace(s[*i]) && ft_inhib(s, *i))
		*i += 1;
	j = *i;
	while (s[j] && ft_isop(s[j], "<>;|&") && ft_inhib(s, j))
		j++;
	ret = ft_strsub(s, *i, j);
	*i = j;
	return (ret);
}

static t_lex	*ft_fill_lex(t_lex *lexer, char *s, int *i)
{
	lexer->com = ft_fill_com(s, i);
	lexer->options = ft_fill_options(s, i);
	if ((lexer->operation = ft_fill_operation(s, i)) != NULL)
		return (lexer);
	return (lexer);
}

int				ft_lex(char *s, char ***env)
{
	t_lex	*lex;
	int		i;
	t_lex	*new;
	int		ret;

	lex = NULL;
	ret = 0;
	i = 0;
	while (s[i])
	{
		new = ft_init_lex();
		new = ft_fill_lex(new, s, &i);
		lex = ft_add_lex(lex, new);
	}
	free(s);
	if (lex && !ft_check_grammar(lex) && !ft_transf_red(lex))
		ft_parse_arg(lex, env, &ret);
	else
		ret = 1;
	ft_free_lex(&lex);
	if (ret < 0)
		ret *= -1;
	update_last_cmd(ret);
	return (ret);
}
