# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 14:10:15 by hbrulin           #+#    #+#              #
#    Updated: 2020/02/03 16:39:04 by hbrulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c copy_env.c parser.c run.c

HEADER = minishell.h 

CFLAGS = -Wall -Werror -Wextra -MMD -I$(HEADER) -g
BUILD_DIR = obj

OBJS = $(SRCS:.c=.o)
OBJ = $(addprefix $(BUILD_DIR)/,$(OBJS))
DPD = $(OBJ:.o=.d)

FTDIR	= libft
FT_LIB	= $(addprefix $(FTDIR)/,libft.a)
FT_INC	= -I $(FTDIR)
FT_LNK	= -L $(FTDIR) -l ft

opti :
	@make -j all

all : make_ft $(NAME)

make_ft:
	@make -C $(FTDIR)

$(NAME): $(OBJ) make_ft
	$(CC) $(OBJ) $(FT_LNK) -lm -o $(NAME) -g
	@echo "$(NAME) created"

$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(FT_INC) -o $@ -c $<

clean:
	@/bin/rm -rf $(BUILD_DIR)
	@echo "Object and DPD files deleted"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Lib deleted"

re : 
	@make fclean
	@make opti

.PHONY: all, clean, fclean, re, opti, make_ft

-include $(DPD)
