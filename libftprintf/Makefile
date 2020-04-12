# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/08 15:50:08 by hbrulin           #+#    #+#              #
#    Updated: 2020/04/12 13:53:49 by hbrulin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =	ft_printf.c ft_struct.c ft_conversion.c ft_flags.c ft_output.c \
		ft_precision.c ft_width.c ft_zero.c ft_conversion_pt2.c \
		ft_precision_data.c ft_width_data.c ft_precision_spec.c ft_precision_s.c

HEADER = printf.h
INC_LIBFT = ../libft
CFLAGS = -Wall -Werror -Wextra -MMD -I$(INC_LIBFT)
BUILD_DIR = obj

OBJS = $(SRCS:.c=.o)
OBJ = $(addprefix $(BUILD_DIR)/,$(OBJS))
DPD = $(OBJ:.o=.d)

opti :
	make -j all

all : $(NAME)

$(NAME): $(OBJ)
	make -C ../libft all
	cp ../libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJ)
	echo "$(NAME) created"
	ranlib $(NAME)
	echo "$(NAME) indexed"

$(BUILD_DIR)/%.o: %.c Makefile
	mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -c $< -o $@

clean:
	/bin/rm -rf $(BUILD_DIR)
	echo "Object and DPD files deleted"

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft fclean
	echo "Lib deleted"

re : 
	make fclean
	make opti

.PHONY: all, clean, fclean, re, opti

-include $(DPD)

for_linux:
	cp ../libft/libft.a ./libft.a
	gcc -c -Wall -Wextra -Werror $(SRCS) $(HEADER) -L./ -lft ../libft/libft.h
	ar rc $(NAME) $(OBJS)
