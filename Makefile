# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miouali <miouali@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/04 15:21:00 by miouali           #+#    #+#              #
#    Updated: 2026/02/14 11:10:39 by miouali          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

DEF_COLOR = \033[0;39m
CYAN    = \033[0;96m
GREEN = \033[0;92m
PURPLE  = \033[0;95m

ERR_LOG = .errors.log 

CC = cc
CFLAGS = -O3 -Wall -Werror -Wextra -Wall -g -I includes -I libft/includes

#Dossiers
SRCS_DIR = srcs/
OBJS_DIR = objs/
HEADER_DIR = includes/

LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a

SRCS_PIPEX = main.c handle_error.c utils.c second_son.c
SRCS_BONUS_PIPEX = main_bonus.c handle_error.c utils.c

SRCS_MANDATORY_PATH = $(addprefix $(SRCS_DIR), $(SRCS_PIPEX))
SRCS_BONUS_PATH = $(addprefix $(SRCS_DIR), $(SRCS_BONUS_PIPEX))

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS_MANDATORY_PATH))
OBJS_BONUS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS_BONUS_PATH))

HEADER = $(HEADER_DIR)pipex.h

RM = rm -rf

all: header start_timer $(NAME) end_timer

header:
	@echo "$(YELLOW) Démarrage de la compilation de Pipex...$(RESET)"

start_timer:
	$(eval START_TIME := $(shell date +%s))

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)
	@rm -f .bonus
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "\n\n$(GREEN) Pipex is ready to be used !$(DEF_COLOR)"

bonus : .bonus
	
.bonus: $(OBJS_BONUS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@touch .bonus
	@echo "\n$(GREEN)✅ Pipex BONUS is ready!$(DEF_COLOR)"
	
TOTAL_FILES := $(words $(SRCS_MANDATORY_PATH))
CURRENT_FILE := 0

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@$(eval PERCENT=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	@printf "\r$(CYAN)🛠️  Compiling Pipex... [%-20s] %d%%" \
		"$(shell printf '#%.0s' $$(seq 1 $$(($(PERCENT) / 5))))" $(PERCENT)
	@$(CC) $(CFLAGS) -c $< -o $@ 2> .temp_err || \
		(printf "\n$(PURPLE)❌ Erreur dans $< :$(RESET)\n" && cat .temp_err >> $(ERR_LOG) && cat .temp_err && rm -f .temp_err)
		

end_timer:
	@$(eval END_TIME := $(shell date +%s))
	@$(eval DURATION := $(shell echo $$(($(END_TIME) - $(START_TIME)))))
	@$(eval ERRORS := $(shell if [ -f $(ERR_LOG) ]; then grep -c "error:" $(ERR_LOG); else echo 0; fi))
	@echo "\n--------------------------------------------------"
	@if [ $(ERRORS) -eq 0 ]; then \
		echo "$(GREEN)✅ COMPILATION TERMINÉE !$(RESET)"; \
	else \
		echo "$(RED)❌ COMPILATION TERMINÉE AVEC DES ERREURS$(RESET)"; \
	fi
	@echo "Temps écoulé : $(DURATION) secondes"
	@echo "  Nombre d'erreurs : $(ERRORS)"
	@echo "--------------------------------------------------"
	@rm -f $(ERR_LOG)

clean:
	$(RM) $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(PURPLE) Objects cleaned!$(DEF_COLOR)"

fclean: clean
		$(RM) $(NAME) .bonus
		@make fclean -C $(LIBFT_DIR)
		@echo "$(PURPLE) $(NAME) deleted!$(DEF_COLOR)"

re: fclean all

.PHONY : all clean fclean re