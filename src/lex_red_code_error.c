/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_red_code_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 05:39:45 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 09:06:22 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "term42.h"

int		lex_err_code(t_lex *lex, int error)
{
	if (error == -2)
		return (error);
	if (lex && lex->next && ft_isred(lex->next, "<>"))
		error = error >= 0 ? 0 : 1;
	return (error);
}
