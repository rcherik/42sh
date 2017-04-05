/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term42.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/13 16:40:14 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 17:26:19 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERM42_H
# define TERM42_H

# include "globbing.h"
# include "libft.h"
# include "get_next_line.h"
# include <termios.h>
# include <termcap.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

# define HIST_F_NAME ".42sh_history"
# define MAX_HIST_FILE 500
# define BUFFER 220000
# define VERBOSE 0
# define PROMPT_COLOR 1
# define GLOBBING 2
# define EVENT_DES 3
# define WRITE_SET 4

typedef struct		s_hist
{
	char			*buff;
	int				pos;
	struct s_hist	*next;
	struct s_hist	*prev;
}					t_hist;

typedef struct		s_set
{
	char			*name;
	char			*user;
	size_t			pid;
	size_t			uid;
	size_t			euid;
	size_t			gid;
	size_t			egid;
}					t_set;

typedef struct		s_comp
{
	char			*s;
	char			type;
	int				len;
	struct s_comp	*head;
	struct s_comp	*next;
	struct s_comp	*prev;
}					t_comp;

typedef struct		s_win
{
	int				line;
	int				col;
}					t_win;

typedef struct		s_shell
{
	t_comp			*comp;
	t_hist			*history;
	t_win			win;
	pid_t			pid;
	char			ctrl_c;
	char			*hist_name;
	char			***env;
	char			*cmd;
	char			*buffer;
	char			*copy_buffer;
	char			*copy_comp;
	char			*prompt;
	char			*key;
	char			*set_path;
	int				copied;
	int				stop;
	int				tab;
	int				cursor_pos;
	int				prompt_len;
	int				event;
	int				err;
	int				*set_opt;
}					t_shell;

typedef struct		s_key
{
	char			*key_code;
	void			(*f)(t_shell *);
}					t_key;

t_shell				*ft_emulate_shell(char ***env);

/*
** prompt.c
*/
int					ft_get_prompt_size(char ***env);
void				ft_put_prompt(void);

/*
** check_spe_char.c
*/
char				*check_spe_char(char *s);
char				*ft_strjoin_slash(char *s, int i);

/*
** ft_alt.c
*/
void				ft_alt_up(t_shell *shell);
void				ft_alt_right(t_shell *shell);
void				ft_alt_left(t_shell *shell);
void				ft_alt_down(t_shell *shell);

/*
** ft_arrows.c
*/
void				ft_right(t_shell *shell);
void				ft_up(t_shell *shell);
void				ft_down(t_shell *shell);
void				ft_left(t_shell *shell);

/*
** ft_comp_list.c
*/
t_comp				*cr_comp_list(char *s, char type);
void				ft_next_comp(t_comp **comp, char *s, char c);
void				create_dot_list(char *path, t_shell *shell);
char				*get_paths(char *s, int flag);
void				create_comp_list(t_shell *s, char *p, char *sch, int count);

/*
** ft_completion.c
*/
void				ft_completion(t_shell *shell);
void				ft_perform_rotation(t_shell *shell);

/*
** ft_ctrl.c
*/
void				ft_free_shell(t_shell *shell);
void				ft_ctrl_d(t_shell *shell);

/*
** ft_cursor.c
*/
void				ft_home(t_shell *shell);
void				ft_home2(t_shell *shell);
void				ft_end(t_shell *shell);

/*
** ft_display_comp.c
*/
void				ft_display_comp(t_shell *shell);

/*
** ft_edit.c
*/
int					ft_display(t_shell *shell);
void				ft_rewrite(char *s);

/*
** ft_event_designators.c
*/
int					get_events(t_shell *shell);

/*
** ft_events.c
*/
int					ft_events(t_shell *shell, char *tmp, int *c, char *buff);
int					ft_events2(t_shell *shell, char *tmp, int *c, char *buff);
int					ft_not_event(char *buff, int i);

/*
** ft_exec_termcaps.c
*/
int					ft_puts(int c);
int					ft_exec_termcaps(char *s);
int					begin_shell(char ***env);

/*
** ft_get_key.c
*/
int					ft_get_key(t_shell *shell);

/*
** ft_history_file.c
*/
int					hist_to_file(t_hist *hist);
int					clear_file(void);
int					list_file(void);
void				ft_get_hist_file(t_shell *shell);

/*
** ft_history_list.c
*/
t_hist				*create_h_elem(char *buff);
void				add_history(t_hist **history, t_shell *shell);
int					last_history(t_hist **history);
void				remove_elem(t_hist *hist, int n);
char				*browse_history(t_hist **history, t_shell *shel, char flag);

/*
** ft_builtin_history.c
*/
int					remove_history(t_hist *hist, int num);
int					free_history(t_hist **list);
int					list_history(t_hist *hist);

/*
** ft_init_term.c
*/
void				ft_get_winsize(t_shell *shell);
void				ft_init_term(void);
void				ft_exit_term(void);
int					is_in_term(void);

/*
** ft_keys.c
*/
void				ft_return(t_shell *shell);
void				ft_del(t_shell *shell);
void				ft_back_del(t_shell *shell);

/*
** ft_no_event.c
*/
int					no_event(t_shell *shell, int n, char *tmp2);
int					no_event2(t_shell *shell, int i, char *tmp2);
int					ft_error2(char *err, char *s);

/*
** ft_sharp.c
*/
int					ft_sharp(t_shell *shell, int i);

/*
** ft_spe_list.c
*/
void				ft_free_comp(t_shell **shell);
void				ft_d_str_free(char *s1, char *s2);
void				ft_spe_list(char *path, char *sch, t_shell *shell);

/*
** ft_special_comp.c
*/
void				ft_special_comp(t_shell *shell, char *s);

/*
** ft_start_shell.c
*/
t_shell				*ft_return_shell(t_shell *shell, char *flag);
void				ft_set_shell(t_shell *shell, char ***env);
void				ft_start_shell(char ***environ);

/*
** ft_cmd_interpretor.c
*/
int					ft_cmd_interpretor(char *s, char ***env);

/*
** ft_error.c
*/
int					ft_error(char *err, char *s);
int					ft_print_error(char *s);

/*
** ft_join_home.c
*/
char				*ft_join_home(char *s, t_shell *sh);
void				ft_rotate(t_shell *sh, char *sch, char *path, int count);
int					put_in_list(t_dirent *ent, char *sch, int ct, t_shell *sh);

/*
** ft_quotes.c
*/
int					check_char2(char c);
int					check_char3(char c);
char				*ft_quotes(char *s, char ***env);
char				*get_dollar3(char *s, int *x, char ***env);
char				*get_dollen(char *s, int *x, char ***env);
char				*get_dollen2(char *s, int *x, char ***env);
char				*add_bs(char *s, int i, int *ptr);
char				*ft_get_sharp_string(char *s, int end);

/*
** ft_remove_char.c
*/
char				*ft_remove_char(char *s, char c);

/*
** ft_add_bq.c
*/
char				*add_bq(char *s, int *x, char ***env);
char				*exec_back_quote(char *s, char ***env);

/*
** back_quote_utilities.c
*/
char				*ft_str_space_join(char *s1, char *s2);
int					check_c(char *s, int i);

/*
** ft_set_set.c
*/
void				ft_set_set(t_shell *shell);

/*
** ft_get_set.c
*/
char				*ft_get_set(char *want);

/*
** ft_init_tabint.c
*/
void				ft_init_tabint(int *t, int len);

/*
** ft_set_builtin.c
*/
int					ft_set_builtin(char **args, char ***env);
int					ft_set_builtin2(char **args, t_shell *shell);
char				**set_to_tab(int fd);

/*
** ft_add_Set.c
*/
void				ft_add_set(char *path, t_shell *shell, char *s1, char *s2);
int					set_event(t_shell *shell);
int					ft_set_prompt(t_shell *shell, char *c);

/*
** ft_set_export.c
*/
int					set_export(t_shell *shell, char **args);

/*
** ft_unset.c
*/
int					ft_unset(char **args, char ***env);

/*
** ft_help_set.c
*/
int					ft_set_help(void);
int					ft_unset_help(void);
#endif
