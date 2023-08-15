# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayylaaba <ayylaaba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/14 19:02:08 by ayylaaba          #+#    #+#              #
#    Updated: 2023/08/15 19:10:01 by ayylaaba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

#CC = cc -O3
CC = clang

MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz #-fsanitize=address

CFLAGS = #-Wall -Wextra -Werror

SRCS = 	main.c \
		get_next_line.c	\
		get_next_line_utils.c \
		ft_strdup.c \
		ft_split.c \
		ft_substr.c \
		ft_strcmp.c \
		ft_strtrim.c \
		ft_isdigit.c \
		parcing_char_extention.c \
		parcing_color.c \
		parcing_player_texture.c \
		move_player.c \
		intersection.c \
		draw_texture.c \

OBJ = ${SRCS:.c=.o}
#OBJBONUS = ${BONUS:.c=.o}

all : ${NAME}

${NAME} : ${OBJ} # $(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

clean :
	rm -f ${OBJ} ${OBJBONUS}

fclean : clean
	rm -f ${NAME}

re : fclean all

