# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelkhad <obelkhad@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/25 09:40:30 by obelkhad          #+#    #+#              #
#    Updated: 2022/08/21 18:47:19 by obelkhad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CFLAGS = -Wall -Wextra -Werror
NAME = cube
SRC += get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRC += main.c src/read_map.c src/utils/utils1.c src/utils/utils2.c src/utils/utils3.c src/vertical_points.c src/horizontal_points.c src/mini_map.c src/rendering.c \
	src/events.c src/ray.c src/map_parsing.c src/map_checker.c src/sprite_gun.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@mv libft/libft.a .
	@make clean -C libft
	@cc $(CFLAGS) -I.  -o $(NAME) $(OBJ) libft.a -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit
%.o:%.c cube.h
	@cc $(CFLAGS) -I.  -Imlx -c $< -o $@
clean:
	@rm -f $(OBJ) libft.a
fclean: clean
	@rm -f $(NAME) libft.a
re: fclean all
