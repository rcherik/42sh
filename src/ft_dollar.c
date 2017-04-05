/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 15:31:39 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/25 21:30:24 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "curl.h"
#include "term42.h"
#include "shell.h"

char			*ft_get_sharp_string(char *s, int end)
{
	char		*tmp;

	tmp = ft_strdup(s);
	while (end - 1 > 0 && s[end - 1] != 32)
		end--;
	while (end - 1 > 0 && s[end - 1] == 32)
		end--;
	tmp[end] = '\0';
	return (tmp);
}

static char		*get_dal(char *s, int *x, char ***env)
{
	int			i;
	int			y;
	char		*dal;
	char		*tmp;

	i = 0;
	y = x[0] + 2;
	while (s[y] && s[y] != '}')
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
	tmp = ft_strsub_len(s, x[0] + 2, i);
	dal = ft_get_env(env, tmp);
	ft_strdel(&tmp);
	return (dal);
}

char			*get_dollar3(char *s, int *x, char ***env)
{
	char	*dal;
	char	*ret;

	dal = get_dal(s, x, env);
	if (dal == NULL)
	{
		ret = ft_strnew(ft_strlen(s) - x[2] - 2);
		ft_strncpy(ret, s, x[0]);
		ret = ft_strjoin_free(&ret, s + x[0] + x[2] + 3);
		x[0] -= 1;
		ft_strdel(&s);
		return (ret);
	}
	ret = ft_strnew(ft_strlen(s) - x[2] + ft_strlen(dal) - 2);
	ft_strncpy(ret, s, x[0]);
	ft_strcpy(ret + x[0], dal);
	ret = ft_strjoin_free(&ret, s + x[0] + 3 + x[2]);
	x[0] += ft_strlen(dal) - 1;
	ft_strdel(&dal);
	ft_strdel(&s);
	return (ret);
}
