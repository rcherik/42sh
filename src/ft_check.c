/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 22:31:38 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 15:25:58 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "curl.h"

/*
** Check the parsing error from the user in the lexem :
** ft_check_operation : More than 3 op or |< |; || ;; <<
** ft_check_next_op : cmd < file > file or cmd > file < file
** ft_check_blank : " > file" or " | cmd ;" or " cmd | ;"
*/

static void	ft_loop_quote(char *cmd, int *i, int *count, char *quote)
{
	char	c;
	char	tmp;

	c = cmd[*i];
	tmp = *quote;
	c = (c == '(') ? ')' : c;
	tmp = (tmp == '(') ? ')' : tmp;
	*i += 1;
	while (cmd[*i] && (cmd[*i] != c || (!ft_inhib(cmd, *i)
				&& (*quote != '\''))))
	{
		if (cmd[*i] == *quote && *quote == '(' && (ft_inhib(cmd, *i)
						&& *quote != '\''))
		{
			*count += 1;
			ft_loop_quote(cmd, i, count, quote);
		}
		*i += 1;
	}
	if (cmd[*i] && cmd[*i] == tmp && (ft_inhib(cmd, *i)
				|| *quote == '\''))
		*count += 1;
	if (cmd[*i] && *quote == ')' && cmd[*i] == *quote && ft_inhib(cmd, *i))
		*count += 1;
}

static int	ft_check_quote(char *cmd, char *quote)
{
	int			i;
	int			count;

	i = -1;
	count = 0;
	if (!quote || !*quote)
		return (0);
	while (cmd[++i])
	{
		if ((cmd[i] == *quote || (*quote == '(' && cmd[i] == ')'))
				&& ft_inhib(cmd, i))
			count++;
		if (ft_isop(cmd[i], "\"'`(") && ft_inhib(cmd, i))
			ft_loop_quote(cmd, &i, &count, quote);
	}
	if (count % 2 == 1)
		return (ft_print_error_free(SYNTAX, ft_strsub(quote, 0, 1)));
	return (ft_check_quote(cmd, quote + 1));
}

static int	ft_check_operation(char *op, char *op2)
{
	if (!op || !op[0])
		return (0);
	if (ft_strlen(op) >= 3)
		return (ft_error(PARSE, ft_sub(op, 0, 2)));
	if (op[1] && ft_isop(op[0], "<;") && ft_isop(op[1], "<;"))
		return (ft_error(PARSE, ft_sub(op, 0, 2)));
	if (ft_strnchar(op, '&') == 1)
		return (ft_error(PARSE, ft_sub(op, 0, 1)));
	if (!op2 || !op2[0])
		return (0);
	if (ft_isop(op[0], "<>") && ft_isop(op2[0], "<>"))
		return (ft_error(PARSE, ft_sub(op2, 0, 1)));
	return (0);
}

static int	ft_check_blank(t_lex *lex)
{
	if (!lex->com[0] && ft_isop(lex->operation[0], "|>&"))
		return (ft_error(PARSE, ft_sub(lex->operation, 0, 2)));
	if ((!lex->prev || !lex->prev->com[0])
			&& ft_isop(lex->operation[0], "|><&")
			&& !(lex->prev && ft_isop(lex->prev->operation[0], "<")))
		return (ft_error(PARSE, ft_sub(lex->operation, 0, 2)));
	if (lex->prev && ft_isop(lex->operation[0], "<>")
			&& !lex->prev->com[0])
		return (ft_error(PARSE, ft_sub(lex->operation, 0, 1)));
	if (count_parenthesis(lex->options) && am_father())
		return (ft_error(PARSE, "("));
	if (count_parenthesis(lex->com) > 0 && lex->options[0] && am_father())
		return (ft_error(PARSE, lex->options));
	if (count_parenthesis(lex->com) > 0 && lex->com[0] != '(')
		return (ft_error(PARSE,
		ft_sub(lex->com, 0, parenthesis_len(lex->com))));
	if (count_bq(lex->com) % 2 != 0 || count_bq(lex->options) % 2 != 0)
		return (ft_error(PARSE, "`"));
	return (0);
}

int			ft_check_grammar(t_lex *lex)
{
	int	err;

	err = 0;
	while (lex->next)
		lex = lex->next;
	while (lex && !err)
	{
		if (lex->prev && !err)
			err = ft_check_operation(lex->operation, lex->prev->operation);
		else if (!lex->prev && !err)
			err = ft_check_operation(lex->operation, NULL);
		if (!err)
			err = ft_check_blank(lex);
		if (!err)
			err = ft_check_quote(lex->com, "\"`'(");
		if (!err)
			err = ft_check_quote(lex->options, "\"`'(");
		if (!err)
			err = ft_glob_check_lex(lex->com, lex->options);
		lex = lex->prev;
	}
	return (err);
}
