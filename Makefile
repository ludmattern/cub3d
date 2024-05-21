# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 16:14:01 by lmattern          #+#    #+#              #
#    Updated: 2024/05/21 14:54:37 by lmattern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, FORCE, fclean, re

CC					:=	cc
NAME				:=	cub3D
CFLAGS				:=	-Wextra -Wall -Werror
MLXFLAGS			:=	-lXext -lX11 -lm
LIBFT				:=	./libft
MINILIBX			:=	./minilibx-linux

HEADERS				:=	-I ./inc/

LIBS				:=	-L$(LIBFT) -lft -L$(MINILIBX) -lmlx
PATHLIBS			:=	$(LIBFT)/libft.a $(MINILIBX)/libmlx.a

DEPS				:=	./inc/cub3D.h

MAINDIR				:=	./src
PARSEDIR			:=	./src/parsing
EXECDIR				:=	./src/exec
UTILSDIR			:=	./src/utils

MAIN_SRC			:=	$(MAINDIR)/main.c \
						$(MAINDIR)/initial_steps.c
PARSE_SRC			:=	$(PARSEDIR)/parse_colors.c \
						$(PARSEDIR)/parse_colors_utils.c \
						$(PARSEDIR)/parse_check_lines.c \
						$(PARSEDIR)/parse_lines.c \
						$(PARSEDIR)/parse_parameters.c \
						$(PARSEDIR)/parse_textures.c \
						$(PARSEDIR)/parse_check_map.c
EXEC_SRC			:=	$(EXECDIR)/calc_wall_dim.c \
						$(EXECDIR)/draw_scene.c \
						$(EXECDIR)/exec_start.c \
						$(EXECDIR)/exit.c \
						$(EXECDIR)/move_amd_cam.c \
						$(EXECDIR)/draw_line.c \
						$(EXECDIR)/init_rc.c
UTILS_SRC			:=	$(UTILSDIR)/utils_memory.c

OBJDIR				:=	./.obj

MAIN_OBJ			:=	$(MAIN_SRC:$(MAINDIR)/%.c=$(OBJDIR)/%.o)
PARSE_OBJ			:=	$(PARSE_SRC:$(PARSEDIR)/%.c=$(OBJDIR)/%.o)
EXEC_OBJ			:=	$(EXEC_SRC:$(EXECDIR)/%.c=$(OBJDIR)/%.o)
UTILS_OBJ			:=	$(UTILS_SRC:$(UTILSDIR)/%.c=$(OBJDIR)/%.o)

OBJS				:=	$(UTILS_OBJ) $(PARSE_OBJ) $(EXEC_OBJ) $(MAIN_OBJ)

all : spinner $(LIBFT) $(MINILIBX) $(NAME) stop_spinner

$(OBJDIR)/%.o: $(UTILSDIR)/%.c $(DEPS) | $(OBJDIR)
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS)

$(OBJDIR)/%.o: $(PARSEDIR)/%.c $(DEPS) | $(OBJDIR)
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS)

$(OBJDIR)/%.o: $(EXECDIR)/%.c $(DEPS) | $(OBJDIR)
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS)

$(OBJDIR)/%.o: $(MAINDIR)/%.c $(DEPS) | $(OBJDIR)
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS)

$(LIBFT)/libft.a: FORCE
	@make -C $(LIBFT) -s

$(MINILIBX)/libmlx.a: FORCE
	@make -C $(MINILIBX) -s

$(NAME): $(LIBFT)/libft.a $(MINILIBX)/libmlx.a $(OBJS) | $(OBJDIR)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(CFLAGS) $(MLXFLAGS) -lreadline \
	-o $(NAME)

spinner:
	@echo "\033[1;32mCompiling cub3D ....\c\033[0m"
	@while :; do \
		for s in / - \\ \|; do \
			printf "\b$$s"; \
			sleep 0.1; \
		done; \
	done & echo $$! > spinner_pid.txt

stop_spinner:
	@kill `cat spinner_pid.txt` 2>/dev/null || true
	@rm -f spinner_pid.txt
	@sleep 0.1; 
	@echo "\nCompilation of cub3D successful."
	@sleep 0.1; 
	@echo "\033[1;32mReady to go ! 🚀\033[0m"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT) -s
	@make clean -C $(MINILIBX) -s

re: fclean all

valgrind: all
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
	./$(NAME) ./maps/map.cub

FORCE:
