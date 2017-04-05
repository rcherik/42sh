/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 03:26:54 by jbail             #+#    #+#             */
/*   Updated: 2014/03/27 07:46:09 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term42.h"
#include "shell.h"
#include <unistd.h>

int				ft_get_prompt_size(char ***environ)
{
	char	*s;
	char	*s2;
	char	*s3;
	int		tmp;
	int		ret;

	ret = 0;
	s = ft_get_env(environ, "LOGNAME");
	s2 = ft_get_last(ft_get_env(environ, "PWD"));
	s3 = ft_get_env(environ, "PROMPT");
	if (s && *s)
		ret++;
	if (s2 && *s2)
		ret++;
	tmp = ft_strlen(s) + ft_strlen(s2) + ft_strlen(s3);
	ret += tmp;
	ft_strdel(&s3);
	ft_strdel(&s2);
	ft_strdel(&s);
	ret = (ret == 0) ? 3 : ret;
	return (ret);
}

static char		*get_color(t_shell *shell)
{
	char		*c;

	c = "YELLOW";
	if (shell->set_opt[PROMPT_COLOR] == 1)
		c = "RED";
	else if (shell->set_opt[PROMPT_COLOR] == 2)
		c = "GREEN";
	else if (shell->set_opt[PROMPT_COLOR] == 3)
		c = "BLUE";
	else if (shell->set_opt[PROMPT_COLOR] == 5)
		c = "BOURG";
	else if (shell->set_opt[PROMPT_COLOR] == 6)
		c = "PURPLE";
	else if (shell->set_opt[PROMPT_COLOR] == 7)
		c = "CYAN";
	else if (shell->set_opt[PROMPT_COLOR] == 8)
		c = "PINK";
	return (c);
}

static void		print_prompt(char *s1, char *s2, t_shell *shell)
{
	char		*c;
	char		*prompt;

	prompt = NULL;
	c = get_color(shell);
	if (s1)
		ft_putcstr_fd(s1, 2, c);
	if (s1 && *s1)
		ft_putstr_fd(" ", 2);
	if (s2)
		ft_putcstr_fd(s2, 2, c);
	if (s2 && *s2)
		ft_putstr_fd(" ", 2);
	if (!(prompt = ft_get_env(shell->env, "PROMPT"))
			|| (prompt && !*prompt))
		ft_putcstr_fd("$> ", 2, c);
	else
		ft_putcstr_fd(prompt, 2, c);
	if (prompt)
		ft_strdel(&prompt);
}

void			ft_put_prompt(void)
{
	t_shell		*shell;
	char		*s1;
	char		*s2;

	shell = ft_return_shell(NULL, NULL);
	if (!isatty(1))
		return ;
	shell->prompt_len = ft_get_prompt_size(shell->env);
	s1 = ft_get_env(shell->env, "LOGNAME");
	s2 = ft_get_last(ft_get_env(shell->env, "PWD"));
	if (is_in_term())
		print_prompt(s1, s2, shell);
	ft_strdel(&s1);
	ft_strdel(&s2);
}
