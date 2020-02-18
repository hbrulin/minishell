# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/14 15:44:39 by hbrulin           #+#    #+#              #
#    Updated: 2020/02/18 14:12:09 by pmouhali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRCS = main.c parse_cmds.c parse_args.c run.c execve.c var_env.c error.c \
	customs.c interpreter.c parsexec.c \
	builtins/ft_echo.c builtins/ft_cd.c builtins/ft_pwd.c builtins/ft_env.c \
	builtins/ft_export.c builtins/ft_unset.c builtins/ft_exit.c \
	try_path.c build_path.c redirect.c pipes.c ft_rmfd.c

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
	@mkdir -p $(BUILD_DIR) $(BUILD_DIR)/builtins
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
