/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 20:25:31 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 05:47:58 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_lex	*ft_go_to_next_op(t_lex *lex, int error_code, char operation)
{
	int	node;

	node = (operation == '&' ? 0 : 1);
	if (ft_isdoubleop(lex->operation, "&|"))
		lex = lex->prev;
	if (node)
	{
		while (lex && (!ft_strequ(lex->operation, ";") &&
					!ft_isdoubleop(lex->operation, "&")))
			lex = lex->prev;
	}
	if (!node)
	{
		while (lex && (!ft_strequ(lex->operation, ";") &&
					!ft_isdoubleop(lex->operation, "|")))
			lex = lex->prev;
	}
	if (lex && ft_isdoubleop(lex->operation, "|") && error_code == 0)
		lex = ft_go_to_next_op(lex, error_code, '|');
	else if (lex && ft_isdoubleop(lex->operation, "&") && error_code != 0)
		lex = ft_go_to_next_op(lex, error_code, '&');
	return (lex);
}

static t_lex	*ft_red_manager(t_lex *lex, char ***env, int *error_code)
{
	int		ret;

	ret = ft_manage_first_red(lex, env);
	if (lex && !ft_isdoubleop(lex->operation, "|&"))
		lex = lex->prev;
	while (lex && lex->prev && !ft_isred(lex, ";&") && ret >= 0 &&
			!ft_isdoubleop(lex->operation, "|"))
	{
		ret = ft_manage_red(lex, ret, env);
		if (ret == -2)
			break ;
		if (lex->prev)
			lex = lex->prev;
	}
	if (lex && lex->next && ret != -2)
		ret = ft_manage_final_red(lex, ret, env);
	wait_for_child();
	*error_code = ret;
	return (lex);
}

static t_lex	*ft_parse_lex(t_lex *lex, char ***env, int *ret)
{
	int			error_code;

	error_code = 0;
	if (ft_isred(lex, "<>|") && !ft_isdoubleop(lex->operation, "&|"))
		lex = ft_red_manager(lex, env, &error_code);
	else if (ft_isdoubleop(lex->operation, "&|"))
		error_code = ft_arg(ft_buildstr(lex), env);
	else if (ft_isred(lex, ";") || !lex->operation[0])
	{
		error_code = ft_arg(ft_buildstr(lex), env);
		*ret = error_code;
		return (lex);
	}
	error_code = lex_err_code(lex, error_code);
	*ret = error_code;
	if (error_code == -2)
		return (NULL);
	if (lex && ft_isdoubleop(lex->operation, "|") && error_code == 0)
		lex = ft_go_to_next_op(lex, error_code, '|');
	else if (lex && ft_isdoubleop(lex->operation, "&") && error_code != 0)
		lex = ft_go_to_next_op(lex, error_code, '&');
	return (lex);
}

void			ft_parse_arg(t_lex *lex, char ***env, int *ret)
{
	while (lex && lex->next)
		lex = lex->next;
	while (lex)
	{
		if (!(!lex->com[0] && lex->operation[0] == ';'))
			lex = ft_parse_lex(lex, env, ret);
		wait_for_child();
		if (!lex)
			return ;
		lex = lex->prev;
	}
}
