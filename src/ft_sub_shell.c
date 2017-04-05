/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 20:46:10 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 15:28:42 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term42.h"
#include "shell.h"
#include "curl.h"
#include <sys/wait.h>
#include <unistd.h>

int				parenthesis_len(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '(' || s[i] == ')') && ft_inhib(s, i))
			return (i);
		i++;
	}
	return (i);
}

int				count_parenthesis(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '(' || s[i] == ')') && ft_inhib(s, i))
			count++;
		i++;
	}
	return (count);
}

static int		exec_sub_shell(char *s, char ***env)
{
	int	child;
	int	stat_loc;
	int	ret;

	ret = 0;
	if ((child = fork()) == -1)
		return (ft_error(MEM_F, NULL) * -2);
	if (child == 0)
	{
		ret = ft_cmd_interpretor(s, env);
		_exit(ret);
	}
	else
		waitpid(child, &stat_loc, 0);
	return (ft_status_interpretor(stat_loc));
}

int				sub_shell(char *s, char ***env)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = s;
	s = ft_strsub(s, 1, ft_strlen(s) - 1);
	ft_strdel(&tmp);
	ret = exec_sub_shell(s, env);
	ft_strdel(&s);
	return (ret);
}
