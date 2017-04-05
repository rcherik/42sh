/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 03:08:55 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 13:42:56 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_unset_help(void)
{
	ft_putstr("The unset builtin will remove a set entry from the");
	ft_putendl(" 42sh_set file. Usage : unset [name]");
	return (0);
}

int			ft_set_help(void)
{
	ft_putstr("Set command displays the acutal .42sh_set file.\n");
	ft_putendltab("Type -v to enable or disable the verbose option:");
	ft_putendltab("When enabled the lines are print as they are read.");
	ft_putendl("This option is off by default.");
	ft_putendltab("Type -g to disable or enable filename expansion (glob).");
	ft_putendl("This option is on by default.");
	ft_putendltab("Type -d to enable or disable the '!' style history.");
	ft_putendl("This option is on by default.");
	ft_putendltab("Type -e [entry] to export a set entry to the environment,");
	ft_putendltab("if the entry does not exist when typed, it will be");
	ft_putendl("created in the .42sh_set file and the environment.");
	ft_putendltab("Type -e [all] to export all the entries from the");
	ft_putendl(".42sh_set file to the the environment.");
	ft_putendltab("Type -c [1 - 8] to choose the prompt color:");
	ft_putendltab("1 for red, 2 for green, 3 for blue, 4 for yellow,");
	ft_putendltab("5 for orange, 6 for purple, 7 for cyan and 8 for pink.");
	ft_putendl("The yellow color is set by default.");
	ft_putendltab("Type set [name] [value] to add the name entry to the");
	ft_putendltab(".42sh_set file as [name]=[value]. If the entry already");
	ft_putendl("exists, its value will be changed with the new value.");
	return (0);
}
