/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sharpbrace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 16:35:21 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/25 21:37:43 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "curl.h"
#include "term42.h"
#include "shell.h"

static char		*get_dal(char *s, int *x, char ***env)
{
	int			i;
	int			y;
	char		*dal;
	char		*tmp;

	i = 0;
	y = x[0] + 3;
	while (s[y] && s[y] != '}' && s[y] != 34)
	{
		y++;
		i++;
	}
	if (i == y)
	{
		x[2] = 0;
		return (NULL);
	}
	x[2] = i;
	tmp = ft_strsub_len(s, x[0] + 3, i);
	dal = ft_get_env(env, tmp);
	ft_strdel(&tmp);
	return (dal);
}

char			*get_dollen(char *s, int *x, char ***env)
{
	char	*dal;
	char	*ret;
	char	*ito;

	dal = get_dal(s, x, env);
	if (dal == NULL)
	{
		ito = ft_itoa(0);
		ret = ft_strnew(ft_strlen(s) - x[2] - 3);
		ft_strncpy(ret, s, x[0]);
		ret = ft_strjoin_free(&ret, ito);
		ret = ft_strjoin_free(&ret, s + x[0] + x[2] + 4);
		x[0] -= 1;
		ft_double_free(ito, s);
		return (ret);
	}
	ito = ft_itoa(ft_strlen(dal));
	ret = ft_strnew(ft_strlen(s) - x[2] + ft_strlen(ito) - 3);
	ft_strncpy(ret, s, x[0]);
	ft_strcpy(ret + x[0], ito);
	ret = ft_strjoin_free(&ret, s + x[0] + 4 + x[2]);
	x[0] += ft_strlen(ito) - 1;
	ft_triple_del(dal, s, ito);
	return (ret);
}
