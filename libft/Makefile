NAME = libft.a

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
		ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
		ft_strcmp.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c\
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_split.c ft_memmove.c ft_strmapi.c ft_itoa.c \
		aff_hex.c ft_putchar.c ft_putstr.c ft_strnew.c ft_strcpy.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_tabdel.c \
		ft_uitoa.c get_next_line.c ft_tab_size.c ft_atoi_base.c ft_is_space.c \
		ft_tablen.c ft_copy_tab.c ft_lst_to_tab.c ft_strcmp.c ft_tab_to_list.c \
		ft_sort_list.c ft_lstprint.c ft_lst_search_n_destroy.c ft_strnjoin.c \
		ft_tab_print.c ft_lstiter_n_cmp.c ft_lstiter_cmp.c ft_sub_tab.c

INC = libft.h
CFLAGS = -Wall -Werror -Wextra -MMD
BUILD_DIR = obj
OBJS = $(SRCS:.c=.o)
OBJ = $(addprefix $(BUILD_DIR)/,$(OBJS))
DPD = $(OBJ:.o=.d)

opti :
	@make -j all

all : $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "$(NAME) created"
	@ranlib $(NAME)
	@echo "$(NAME) indexed"
	
$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(BUILD_DIR)
	@gcc $(CFLAGS) -I $(INC) -c $< -o $@

clean:
	@/bin/rm -rf $(BUILD_DIR)
	@echo "Object and DPD files deleted"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Lib deleted"

re :
	@make fclean
	@make opti

.PHONY: all, clean, fclean, re

-include $(DPD)

for_linux:
	gcc -c $(FLAGS) $(SRCS) -I./ libft.h
	ar rc $(NAME) $(OBJS)
