# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/27 14:59:24 by mdufaud           #+#    #+#              #
#    Updated: 2014/03/27 17:31:35 by rcherik          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh
CFLAGS = cc -Wall -Wextra -Werror
OFLAGS = -I libft/includes/. -I ./includes/.
LFLAGS = -L libft -lft -L /usr/lib -ltermcap
LIB = libft/libft.a
MKLIB = make -C libft
PATH_SRC = src
PATH_OBJ = obj
SRC = alternate_path_check.c\
	  update_last_cmd.c\
	  ft_father.c\
	  back_quote.c\
	  back_quote_utilities.c\
	  check_spe_char.c\
	  exec_file.c\
	  ft_add_bq.c\
	  ft_add_set.c\
	  ft_add_to_glob.c\
	  ft_alt.c\
	  ft_arg.c\
	  ft_arrows.c\
	  ft_atty.c\
	  ft_bracket.c\
	  ft_builtin.c\
	  ft_builtin_echo.c\
	  ft_builtin_env.c\
	  ft_builtin_help.c\
	  ft_builtin_history.c\
	  ft_builtin_type.c\
	  ft_cd.c\
	  ft_check.c\
	  ft_check_glob.c\
	  ft_child.c\
	  ft_cmd_interpretor.c\
	  ft_comp_list.c\
	  ft_completion.c\
	  ft_ctrl.c\
	  ft_curl.c\
	  ft_curl_uti.c\
	  ft_cursor.c\
	  ft_dir.c\
	  ft_display_comp.c\
	  ft_dollar.c\
	  ft_echo_base.c\
	  ft_edit.c\
	  ft_env.c\
	  ft_error.c\
	  ft_error2.c\
	  ft_event_designators.c\
	  ft_events.c\
	  ft_exec.c\
	  ft_exec_termcaps.c\
	  ft_export.c\
	  ft_free.c\
	  ft_free_globbing.c\
	  ft_get.c\
	  ft_get_key.c\
	  ft_get_set.c\
	  ft_glob_check.c\
	  ft_globbing.c\
	  ft_grammar.c\
	  ft_grammar_op.c\
	  ft_help_set.c\
	  ft_history.c\
	  ft_history_file.c\
	  ft_history_list.c\
	  ft_init_globbing.c\
	  ft_init_tabint.c\
	  ft_init_term.c\
	  ft_join_home.c\
	  ft_keys.c\
	  ft_lexer.c\
	  ft_lexer_op.c\
	  ft_match.c\
	  ft_no_event.c\
	  ft_parse.c\
	  ft_pipe.c\
	  ft_print_gnl.c\
	  ft_quote.c\
	  ft_quotes.c\
	  ft_red_final.c\
	  ft_red_first.c\
	  ft_redirection.c\
	  ft_remove_char.c\
	  ft_set.c\
	  ft_set_builtin.c\
	  ft_set_builtin2.c\
	  ft_sharp.c\
	  ft_sharpbrace.c\
	  ft_sharpbrace2.c\
	  ft_signal.c\
	  ft_signal_interpretor.c\
	  ft_spe_list.c\
	  ft_split.c\
	  ft_start_shell.c\
	  ft_sub_shell.c\
	  ft_tab_uti.c\
	  ft_transf_red.c\
	  ft_unset.c\
	  ft_utilities.c\
	  get_next_line.c\
	  gnl_utilities.c\
	  lex_red_code_error.c\
	  main.c\
	  prompt.c
OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all : $(NAME)

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@$(CFLAGS) $(OFLAGS) -o $@ -c $^

$(LIB) :
	@$(MKLIB)

$(NAME) : $(LIB) $(OBJ)
	@echo "\033[32m[ 42sh objects done ]\033[00m"
	@$(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@echo "\033[32m[ 42sh compiled ]\033[00m"

lib :
	@$(MKLIB)
	@make
	@echo "\033[32m[ Library done && 42sh compiled ]\033[00m"

clean :
	@$(MKLIB) clean
	@rm -f $(OBJ)
	@echo "\033[31m[ 42sh : objects deleted ]\033[00m"

fclean : clean
	@$(MKLIB) fclean
	@rm -f $(NAME)
	@echo "\033[31m[ 42sh : ./42sh deleted ]\033[00m"

re : fclean all

.PHONY : fclean re clean all
