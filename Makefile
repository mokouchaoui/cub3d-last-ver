# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 15:35:54 by mokoucha          #+#    #+#              #
#    Updated: 2022/11/09 01:41:24 by mokoucha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.c \
			src/parser/parser.c \
			src/parser/filler.c \
			src/parser/parser_checker.c \
			src/parser/parser_fill.c \
			src/parser/parser_get.c \
			src/get_next_line/get_next_line.c \
			src/get_next_line/get_next_line_utils.c \
			src/utils/utils_math.c \
			src/utils/utils_free.c \
			src/utils/utils_general.c \
			src/graphics/draw.c \
			src/graphics/textures_loader.c \
			src/raycasting/raycasting.c \
			src/raycasting/raycasting_get.c \
			src/raycasting/raycasting_loops.c \
			src/raycasting/raycasting_utils.c \
			src/player/player_movements.c \
			src/player/player_camera.c \
			src/graphics/draw_utils.c

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -Iinclude/

NAME	=	cub3d

%.o: %.c
	@$(CC) $(CFLAGS) -Wall -Wextra -Werror -Imlx -c $< -o $@ -g

# %.o: %.c
# 	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME):	$(OBJS)
			@$(MAKE) -C ./mlx
			@$(MAKE) -C ./libft
			@cp mlx/libmlx.a .
			@cp libft/libft.a .
			@$(CC) $(OBJS) -Lmlx -lmlx libft.a -framework OpenGL -framework AppKit -o $(NAME) -g
			@echo '\033[1;35mCub3d created! 🎮\033[0;00m';

# LINUX:	$(OBJS)
# 		@$(MAKE) -C ./libft
# 		@cp libft/libft.a .
# 		@$(CC) $(OBJS) libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
# 		@echo '\033[1;35mCub3d! 🎮\033[0;00m';

all:		$(NAME)

clean:
			@$(RM) $(OBJS)
			@$(MAKE) clean -C ./mlx
			@$(MAKE) clean -C ./libft
			@echo '\033[1;37mCleaning!... 🧹';

fclean:		clean
			@$(RM) $(NAME)
			@$(MAKE) fclean -C ./libft
			@$(RM) libmlx.a
			@$(RM) libft.a
			@echo '\033[1;37mAll is clean!... 🧹';

re:			fclean all

.PHONY:		all clean fclean re
