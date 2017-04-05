/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 20:59:05 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/26 23:47:42 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODE_H
# define ERROR_CODE_H

/*
** ft_error.c
*/
int		ft_error(char *err, char *s);
int		ft_print_error(char *s);
int		ft_print_error_free(char *err, char *s);
int		ft_single_access(char *arg, char *is);
int		ft_access_newfile(char *arg);

# define SEG_FAULT "Segmentation fault."
# define FLOAT_P_EXCEPT "Floating point exception (divide by zero)."
# define BROKEN_PIPE "Broken pipe."
# define BUS_ERROR "Bus error."
# define FILE_FAIL "could not open : "
# define ARG_LIST_LEN "argument list too long: "
# define NO_EVENT "no such event: "
# define NO_WORD_EVENT "no such word in event."
# define ILL_OP "illegal option -- "
# define MEM_F "ressources currently unavailable. Fork failed."
# define MEM_M "not enough memory. Malloc failed."
# define MEM_P "no file descriptor available. Pipe failed."
# define COM_NOT_FOUND "command not found: "
# define PERM_DENY "permission denied: "
# define VAR_EQ "var name contain char = in: "
# define NO_FILE_DIR "no such file or directory: "
# define MUCH_ARG "too many arguments for: "
# define LESS_ARG "not enough arguments for: "
# define NOT_DIR "not a directory: "
# define IS_DIR "is a directory: "
# define PARSE "parse error near "
# define SYNTAX "syntax error: "
# define PATTERN "bad pattern : "
# define ENV_NOT_FOUND "environment not found : "
# define ENV_NOT_SET "environment not set."
# define SET_NOT_FOUND "variable not found: "
# define AMBIGOUS "ambigous redirection output."
#endif
