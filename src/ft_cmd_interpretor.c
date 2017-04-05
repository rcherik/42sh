/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_interpretor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 19:25:13 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 03:58:57 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "term42.h"
#include <stdlib.h>

int		ft_cmd_interpretor(char *str, char ***env)
{
	int		ret;
	char	*s;

	ret = 1;
	s = ft_epur_grammar(str, "<;>|&");
	if (!s)
		free(str);
	else if (!s[0])
		free(s);
	else
	{
		ft_exit_term();
		ret = ft_lex(s, env);
		ft_init_term();
	}
	return (ret);
}
