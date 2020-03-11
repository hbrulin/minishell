# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 15:44:39 by hbrulin           #+#    #+#              #
#    Updated: 2020/03/11 16:38:48 by hbrulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRCS = main.c parsing/parse_cmds.c parsing/parse_args.c exec/run.c exec/execve.c \
	builtins/var_env.c error.c builtins/customs.c builtins/ft_cd.c \
	builtins/ft_pwd.c builtins/ft_export.c builtins/ft_unset.c \
	parsing/interpreter.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_exit.c \
	parsexec.c exec/build_path.c fds/redirect.c fds/pipes.c fds/ft_rmfd.c \
	parsing/parse_args_utils.c parsing/expand.c parsing/copy_tab_void.c \
	parsing/ls_part.c parsing/parse_args_utils2.c parsing/parse_args2.c fds/pipes_exe.c \
	fds/pipes_utils.c

SRC_DIR = srcs
INC_DIR = inc
BUILD_DIR = obj
CFLAGS = -Wall -Werror -Wextra -MMD -I $(INC_DIR) -g

OBJS = $(SRCS:.c=.o)
OBJ = $(addprefix $(BUILD_DIR)/,$(OBJS))
DPD = $(SRCS:.c=.d)

FTDIR	= libft
FT_LIB	= $(addprefix $(FTDIR)/,libft.a)
FT_INC	= -I $(FTDIR)
FT_LNK	= -L $(FTDIR) -l ft

FTDIRP	= libftprintf
FT_LIBP	= $(addprefix $(FTDIRP)/,libftprintf.a)
FT_INCP	= -I $(FTDIRP)
FT_LNKP	= -L $(FTDIRP) -l ftprintf

opti :
	@make -j all

all : make_ft make_ftp $(NAME)

make_ft:
	@make -C $(FTDIR)

make_ftp:
	@make -C $(FTDIRP)

$(NAME): $(OBJ) make_ft make_ftp
	$(CC) $(OBJ) $(FT_LNK) $(FT_LNKP) -lm -o $(NAME) -g
	@echo "$(NAME) created"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@mkdir -p $(BUILD_DIR) $(BUILD_DIR)/builtins $(BUILD_DIR)/exec $(BUILD_DIR)/fds $(BUILD_DIR)/parsing
	$(CC) $(CFLAGS) $(FT_INC) $(FT_INCP) -o $@ -c $<

clean:
	@/bin/rm -rf $(BUILD_DIR)
	@echo "Object and DPD files deleted"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Lib deleted"

re : 
	@make fclean
	@make opti

.PHONY: all, clean, fclean, re, opti, make_ft, make_ftp

-include $(DPD)

for_linux:
	gcc -g -Wall -Wextra -Werror -I./inc/ srcs/*.c srcs/builtins/*.c -L./libftprintf/ -lftprintf -I./libftprintf/ -I./libft/ libft/libft.a
