/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/07 21:20:49 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/26 04:47:40 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "curl.h"

static int	ft_check_bracket_pat(char *s, int i)
{
	int	j;

	while (s[i])
	{
		if (s[i] == '[' && ft_inhib(s, i))
		{
			if (s[i + 1])
			{
				j = 0;
				while ((s[i + j + 2] != ']' && s[i + j + 2] != '\0')
						|| (s[i + j + 2] == ']' && !ft_inhib(s, i + j + 2)))
					j++;
				if (s[i + j + 2] == '\0')
					return (i);
				i += j + 1;
			}
			else
				return (i);
		}
		i++;
	}
	return (-1);
}

static int	ft_acc_loop(char *s, int i, int *err)
{
	while ((s[i] && s[i] != '}')
			|| ((s[i] == '}' && ft_inhib(s, i))))
	{
		if (s[i] == ',' && !(*err & 1))
			*err += 1;
		if (s[i] == ' ' && !(*err & 2))
			*err += 2;
		i++;
	}
	return (i);
}

static int	ft_check_acc(char *s, int i)
{
	int	err;
	int	j;

	while (s[i])
	{
		err = 0;
		if (s[i] == '{' && ft_inhib(s, i))
		{
			j = 0;
			j = ft_acc_loop(s, i, &err);
			if ((err & 1) && (err & 2) && i > 0)
				return (i);
			else if ((err & 1) && (err & 2) && i == 0)
				return (-1);
			i += j;
		}
		i++;
	}
	return (0);
}

static int	ft_glob_check(char *s)
{
	int	n;
	int	err;
	int	i;

	i = 0;
	n = 0;
	err = 0;
	while (s[i] && err == 0)
	{
		if (s[i] == '[' && ft_inhib(s, i) && !(n & 1))
		{
			n += 1;
			if ((err = ft_check_bracket_pat(s, i)) == 0)
				err = -1;
			else if (err == -1)
				err = 0;
		}
		if (err == 0 && s[i] == '{' && ft_inhib(s, i) && !(n & 2))
		{
			n += 2;
			err = ft_check_acc(s, i);
		}
		i++;
	}
	return (err);
}

int			ft_glob_check_lex(char *s1, char *s2)
{
	int	err;

	err = 0;
	err = ft_glob_check(s1);
	if (err)
		return (ft_error(PATTERN, ft_sub(s1, err, err + 1)));
	err = ft_glob_check(s2);
	if (err)
		return (ft_error(PATTERN, ft_sub(s2, err, err + 1)));
	return (0);
}
