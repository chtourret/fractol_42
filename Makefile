# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctourret <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/19 16:14:20 by ctourret          #+#    #+#              #
#    Updated: 2017/06/01 13:13:01 by ctourret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : clean fclean re

NAME = fractol

CC = gcc

LDFLAGS = -Wall -Wextra -Werror -O3

LDLIBFT = -L libft/ -lft

LDMINI = -L minilibx_macos/ -lmlx -framework OpenGL -framework Appkit

SRC = src/hook.c\
	  src/mouse.c\
	  src/julia_ship.c\
	  src/mandel_tri.c\
	  src/tools.c\
	  src/main.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

OBJ : $(OBJ)
	@$(CC) $(LDFLAGS) -c $(SRC)

$(NAME) : $(OBJ)
	@make -C libft
	@make -C minilibx_macos
	@$(CC) $(LDFLAGS) $(OBJ) $(LDLIBFT) $(LDMINI) -o $(NAME)

clean :
	@make clean -C libft
	@make clean -C minilibx_macos
	@rm -f $(OBJ)

fclean : clean
	@make fclean -C libft
	@rm -f $(NAME)

help :
	@echo ← ⇢ ⇡ ⇣ : Deplace la fractale
	@echo Delete : Verrouille le mouvement de la souris
	@echo Clear : Reset la fractale
	@echo Q / E : augmente/diminue les iterations
	@echo C / X : Modifie les couleurs
	@echo + / - : Zoom/Dezoom a partir du centre

re : fclean all
