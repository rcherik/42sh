/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sharp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 21:16:12 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/25 21:30:32 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "curl.h"
#include "error_code.h"
#include <stdlib.h>
#include <unistd.h>

static int		check_for_space(char *s, int i)
{
	int		j;
	int		check;

	j = 0;
	check = 0;
	while (j < i)
	{
		if ((s[j] != 9 && s[j] != 32) && check == 0)
			check = 1;
		if ((s[j] == 9 || s[j] == 32) && ft_inhib(s, j) && check == 1)
			check = 2;
		j++;
	}
	if (check == 2)
		return (0);
	return (1);
}

static int		ft_sharp_case2(t_shell *shell, int pos)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(shell->buffer);
	ft_bzero(shell->buffer, BUFFER + 1);
	i = pos;
	while (tmp[i] && (tmp[i] != ';' || (tmp[i] == ';' && !ft_inhib(tmp, i))))
		i--;
	if (ft_strnequ(tmp + i + 1, "!#", 2))
	{
		ft_strncpy(shell->buffer, tmp, pos);
		ft_strncpy(shell->buffer + pos, tmp, i);
		ft_strcpy(shell->buffer + pos + i, tmp + pos + 2);
	}
	else
	{
		ft_strncpy(shell->buffer, tmp, pos);
		ft_strncpy(shell->buffer + pos, tmp, i + 1);
		ft_strcpy(shell->buffer + pos + i + 1, tmp + pos + 2);
	}
	ft_strdel(&tmp);
	return (0);
}

static int		ft_sharp_case1(t_shell *shell, int i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(shell->buffer);
	ft_bzero(shell->buffer, BUFFER + 1);
	ft_strncpy(shell->buffer, tmp, i);
	tmp2 = ft_get_sharp_string(shell->buffer, i);
	ft_strcpy(shell->buffer + i, tmp2);
	ft_strcpy(shell->buffer + i + ft_strlen(tmp2), tmp + i + 2);
	free(tmp);
	free(tmp2);
	return (0);
}

static int		ft_spe_sharp(char *s, int pos)
{
	int		i;
	int		check;

	if (s[0] == ';' && s[1] == '!')
		return (0);
	i = 0;
	check = 0;
	while (i < pos)
	{
		if (s[i] == 32 && ft_inhib(s, i))
			return (0);
		if (s[i] == ';' && ft_inhib(s, i))
			check = 1;
		i++;
	}
	if (check)
		return (1);
	return (0);
}

int				ft_sharp(t_shell *shell, int i)
{
	int		spec;

	spec = 0;
	if (i == 0 || (check_for_space(shell->buffer, i)
			&& ((spec = ft_spe_sharp(shell->buffer, i)) == 0)))
	{
		ft_error2("no such word in event", NULL);
		return (-1);
	}
	if ((ft_strlen(shell->buffer) * 2) >= (BUFFER))
	{
		ft_error2("event designator !# would exceed the buffer", NULL);
		return (-1);
	}
	shell->event = 1;
	if (!spec)
		return (ft_sharp_case1(shell, i));
	else
		return (ft_sharp_case2(shell, i));
}
