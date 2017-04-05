/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 17:46:36 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 11:19:06 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>

int		main(int argc, char **argv, char **environ)
{
	char	**env;

	env = ft_init_env(environ);
	if (!isatty(0))
		ft_atty(&env);
	if (argc == 1)
	{
		ft_start_shell(&env);
		ft_exit_term();
	}
	else if (argc == 2)
		exec_file(argv[1], &env);
	(void)argv;
	return (0);
}
