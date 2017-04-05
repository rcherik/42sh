/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_last_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 08:45:22 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 08:51:05 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "libft.h"
#include "shell.h"
#include <stdlib.h>

void	update_last_cmd(int code)
{
	t_shell		*shell;
	char		*s;

	shell = ft_return_shell(NULL, NULL);
	if (!shell)
		return ;
	s = ft_itoa(code);
	ft_add_set(shell->set_path, shell, "?", s);
	free(s);
}
