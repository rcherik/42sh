# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/19 14:45:20 by mdufaud           #+#    #+#              #
#    Updated: 2014/03/27 12:07:22 by jbail            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = cc -Wall -Wextra -Werror
IFLAGS = -I includes
PATH_SRC = src
PATH_OBJ = obj
FIRST_SRC = $(addprefix $(PATH_SRC)/, $(shell ls -1 $(PATH_SRC) | head -n 1))
SRC = ft_2dlen.c\
	  ft_triple_del.c\
	  ft_double_free.c\
	  ft_tab_new.c\
	  ft_addtab.c\
	  ft_atoi.c\
	  ft_atoi_free.c\
	  ft_bzero.c\
	  ft_debugc.c\
	  ft_strlcat.c\
	  ft_debugchar.c\
	  ft_debugfun.c\
	  ft_debugnbr.c\
	  ft_debugn.c\
	  ft_debugs.c\
	  ft_debugstr.c\
	  ft_debugstrn.c\
	  ft_epur.c\
	  ft_free_tab.c\
	  ft_isalnum.c\
	  ft_isalpha.c\
	  ft_isascii.c\
	  ft_isprint.c\
	  ft_isdigit.c\
	  ft_isspace.c\
	  ft_itoa.c\
	  ft_lstadd.c\
	  ft_lstnew.c\
	  ft_memalloc.c\
	  ft_memccpy.c\
	  ft_memchr.c\
	  ft_memdel.c\
	  ft_memcmp.c\
	  ft_memcpy.c\
	  ft_memmove.c\
	  ft_memset.c\
	  ft_print_green.c\
	  ft_print_greenendl.c\
	  ft_print_list.c\
	  ft_print_tab.c\
	  ft_print_tab_fd.c\
	  ft_printlist.c\
	  ft_putcendl.c\
	  ft_putcendl_fd.c\
	  ft_putendltab.c\
	  ft_putdendl.c\
	  ft_putendl.c\
	  ft_putendl_fd.c\
	  ft_putdendl_fd.c\
	  ft_putchar.c\
	  ft_putstr_fd.c\
	  ft_strclen.c\
	  ft_strequ.c\
	  ft_strjoin_free.c\
	  ft_strlen.c\
	  ft_strtjoin.c\
	  ft_tabdup.c\
	  ft_tablen.c\
	  ft_putchar_fd.c\
	  ft_putdstr.c\
	  ft_putdstr_fd.c\
	  ft_putcstr.c\
	  ft_putcstr_fd.c\
	  ft_putnbr.c\
	  ft_putnbr_fd.c\
	  ft_putstr.c\
	  ft_putswag.c\
	  ft_strcat.c\
	  ft_strchr.c\
	  ft_strclr.c\
	  ft_strcmp.c\
	  ft_strcpy.c\
	  ft_strdel.c\
	  ft_strdigit.c\
	  ft_strdup.c\
	  ft_strdup_free.c\
	  ft_strncat.c\
	  ft_strnchar.c\
	  ft_strncmp.c\
	  ft_strncpy.c\
	  ft_strnequ.c\
	  ft_strnew.c\
	  ft_strnstr.c\
	  ft_strrchr.c\
	  ft_strsplit.c\
	  ft_str_all_split.c\
	  ft_strstr.c\
	  ft_strsub.c\
	  ft_strsub_free.c\
	  ft_strsub_len.c\
	  ft_strcat.c\
	  ft_strjoin.c\
	  ft_strjoin_c.c\
	  ft_strjoin_c_free.c\
	  ft_strtrim.c\
	  ft_sub.c
OBJ = $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRC))

all: $(NAME)

$(PATH_OBJ)/%.o : $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@$(CFLAGS) $(IFLAGS) -o $@ -c $^
	@ if [ $^ == $(FIRST_SRC) ]; then \
			echo "\033[32;01mLibft : [ \033[00m\c"; \
		fi
	@echo "\033[32;01m.\033[00m\c"

$(NAME): $(OBJ)
	@echo "\033[32;01m ]\033[00m"
	@echo "\033[32m[ Objects done ]\033[00m"
	@ar rcs $@ $^
	@echo "\033[32m[ Library done ]\033[00m"

clean:
	@rm -f $(OBJ)
	@echo "\033[31m[ Objects deleted ]\033[00m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31m[ $(NAME) deleted ]\033[00m"

re: fclean all

.PHONY: all clean fclean re
