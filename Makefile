# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 09:40:30 by obelkhad          #+#    #+#              #
#    Updated: 2022/08/21 15:16:29 by obelkhad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Wextra -Werror -g
NAME = cube
SRC = libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c \
	libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c \
	libft/ft_putendl_fd.c libft/ft_putnbr_fd.c libft/ft_putstr_fd.c libft/ft_split.c libft/ft_split2.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_striteri.c \
	libft/ft_strjoin.c libft/ft_strlcat.c libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c \
	libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c libft/ft_lstadd_front.c libft/ft_lstlast.c libft/ft_lstnew.c libft/ft_lstsize.c \
	libft/ft_lstadd_back.c libft/ft_lstdelone.c libft/ft_lstclear.c libft/ft_lstiter.c libft/ft_lstmap.c libft/ft_strcmp.c
SRC += get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRC += main.c src/read_map.c src/utils/utils1.c src/utils/utils2.c src/utils/utils3.c src/vertical_points.c src/horizontal_points.c src/mini_map.c src/rendering.c \
	src/events.c src/ray.c src/map_parsing.c src/map_checker.c src/sprite_gun.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@# make -C libft
	@cc $(CFLAGS) -I.  -o $(NAME) $(OBJ) -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
%.o:%.c cube.h
	@cc $(CFLAGS) -I.  -Imlx -c $< -o $@
clean:
	@rm -f $(OBJ)
fclean: clean
	@rm -f $(NAME)
re: fclean all
