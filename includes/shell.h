/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 15:03:50 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 17:27:03 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"
# include "error_code.h"

# define BUILTIN_NUM 12

typedef struct		s_built
{
	char			*cmd;
	int				(*f)(char **, char ***);
}					t_built;

typedef struct		s_lex
{
	char			*com;
	char			*options;
	char			*operation;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;

void				ft_signal(void);
int					ft_print_gnl(int fd);

/*
** ft_father.c
*/
int					am_father(void);

/*
** update_last_cmd.c
*/
void				update_last_cmd(int code);

/*
** lex_red_code_error.c
*/
int					lex_err_code(t_lex *lex, int error);

/*
** ft_transf_red.c
*/
int					ft_transf_red(t_lex *lex);

/*
** alternate_path_check.c
*/
int					ft_alternate_path_check(char **s, char ***env);

/*
** exec_file.c
*/
int					exec_file(char *s, char ***env);

/*
** ft_sub_shell.c
*/
int					sub_shell(char *s, char ***environ);
int					count_parenthesis(char *s);
int					parenthesis_len(char *s);

/*
** ft_signal_interpretor.c
*/
int					ft_signal_interpretor(int sig);

/*
** back_quotes.c
*/
char				*exec_back_quote(char *s, char ***env);
char				*ft_str_space_join(char *s1, char *s2);
int					count_bq(char *s);

/*
** ft_atty.c
*/
void				ft_atty(char ***env);

/*
** ft_export.c
*/
int					ft_export(char **args, char ***env);

/*
** ft_builtin_set.c
*/
int					ft_builtin_set(char **args, char ***set);

/*
** ft_child.c
*/
void				wait_for_child(void);

/*
** ft_builtin_env.c
*/
int					ft_env(char **args, char ***environ);
int					ft_print_env(char ***environ);

/*
** ft_history.c
*/
int					ft_history(char **args, char ***env);

/*
** ft_builtin_help.c
*/
int					ft_builtin_help(char **args, char ***env);

/*
** ft_builtin_type.c
*/
int					ft_builtin_type(char **args, char ***env);

/*
** ft_builtin_echo.c
*/
int					ft_builtin_echo(char **args, char ***env);

/*
** ft_echo_base.c
*/
int					ft_get_octal(char *s, int pos);
int					ft_get_hexa(char *s, int pos);

/*
** ft_split.c
*/
char				**ft_quotesplit(char *s, char **env);

/*
** ft_builtin.c
*/
t_built				*ft_ret_builtins(void);
int					ft_exit(char **args, char ***env);

/*
** ft_quote.c
*/
char				**ft_init_transform(char **tab);

/*
** ft_arg.c
*/
char				**ft_transform(char **tab);
int					ft_check_builtin(t_built *built, char **args, char ***env);
int					ft_arg(char *s, char ***env);
char				*ft_check_all(char *s, char **all);

/*
** ft_cd.c
*/
int					ft_cd(char **args, char ***env);

/*
** ft_env.c
*/
int					ft_setenv(char **args, char ***env);
int					ft_set_env(char *name, char *value, char ***env);
int					ft_unsetenv(char **args, char ***env);

/*
** ft_error.c
*/
int					ft_error(char *err, char *s);
int					ft_print_error(char *s);
int					ft_print_error_free(char *err, char *s);
int					ft_single_access(char *arg, char *is);
int					ft_access_newfile(char *arg);

/*
** ft_exec.c
*/
int					ft_exec(char **s, char ***env, char *place);
int					ft_exec_path(char **args, char ***env);
int					ft_status_interpretor(int stat_loc);

/*
** ft_free.c
*/
char				**ft_tabdel(char ***env, int focus);
void				ft_free_lex(t_lex **lex);
void				ft_free_env(char ***env);

/*
** ft_get.c
*/
char				*ft_get_last(char *s);
char				*ft_get_env(char ***env, char *want);
char				**ft_init_env(char **env);

/*
** ft_grammar_op.c
*/
int					ft_isop(char c, char const *gram);
int					ft_isdoubleop(char *s, char const *gram);
void				ft_loop_gram(char *s, int *i);
void				ft_loop_gram_and_fill(char *s, int *i, char *tmp, int *j);

/*
** ft_glob_check.c
*/
int					ft_glob_check_lex(char *s1, char *s2);

/*
** ft_grammar.c
*/
char				*ft_epur_grammar(char *s, char const *gram);

/*
** ft_lexer.c
*/
int					ft_lex(char *s, char ***env);

/*
** ft_lexer_op.c
*/
int					ft_isred(t_lex *lex, char const *gram);
char				*ft_buildstr(t_lex *lex);
void				ft_print_lexer(t_lex *lex);
t_lex				*ft_init_lex(void);
t_lex				*ft_add_lex(t_lex *old, t_lex *new);

/*
** ft_parse.c
*/
void				ft_parse_arg(t_lex *lex, char ***env, int *ret);

/*
** ft_red_first.c
*/
int					ft_fd_open(char *file);
int					ft_manage_first_red(t_lex *lex, char ***env);

/*
** ft_redirection.c
*/
int					ft_close_fd(int fd);
int					ft_manage_red(t_lex *lex, int ret, char ***env);

/*
** ft_red_last.c
*/
int					ft_ctfd(int fd1, int fd2, int fd3);
int					ft_manage_final_red(t_lex *lex, int ret, char ***env);

/*
** ft_pipe.c
*/
int					ft_first_pipe(char *arg, char ***env);
int					ft_multi_pipe(int pipex, char *arg, char ***env);
int					ft_final_pipe(int pipex, char *arg, char ***env);

/*
** ft_check.c
*/
int					ft_check_grammar(t_lex *lex);

#endif
