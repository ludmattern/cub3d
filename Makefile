# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmattern <lmattern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 16:14:01 by lmattern          #+#    #+#              #
#    Updated: 2024/05/14 13:39:24 by lmattern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, FORCE, fclean, re, bash_spinner, stop_bash_spinner, \
bonus, zsh_spinner, stop_zsh_spinner

CC					:=	cc
NAME				:=	cub3D
CFLAGS				:=	-Wextra -Wall -Werror
LIBFT				:=	./libft
MINILIBX			:=	./minilibx-linux

HEADERS				:=	-I ./inc/

LIBS				:=	-L$(LIBFT) -lft -L$(MINILIBX) -lmlx
PATHLIBS			:=	$(LIBFT)/libft.a $(MINILIBX)/libmlx.a

DEPS				:=	./inc/cub3D.h

MAINDIR				:=	./src/

MAIN_SRC			:=	$(MAINDIR)/main.c

OBJDIR				:=	./.obj

MAIN_OBJ			:=	$(MAIN_SRC:$(MAINDIR)/%.c=$(OBJDIR)/%.o)

OBJS				:=	$(MAIN_OBJ)

all : spinner $(LIBFT) $(MINILIBX) $(NAME) stop_spinner

$(OBJDIR)/%.o: $(EXECDIR)/%.c $(DEPS) | $(OBJDIR)
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS)

$(OBJDIR)/%.o: $(PARSEDIR)/%.c $(DEPS) | $(OBJDIR)
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS)

$(OBJDIR)/%.o: $(MAINDIR)/%.c $(DEPS) | $(OBJDIR)
	@$(CC) $(CFLAGS) -g -o $@ -c $< $(HEADERS)

$(LIBFT)/libft.a: FORCE
	@make -C $(LIBFT) -s

$(MINILIBX)/libft.a: FORCE
	@make -C $(MINILIBX) -s

$(NAME): $(LIBFT)/libft.a $(OBJS) | $(OBJDIR)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(CFLAGS) -lreadline -o $(NAME)

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

re: fclean all

FORCE:
