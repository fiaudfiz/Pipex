# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fiaudfiz <fiaudfiz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/04 15:21:00 by miouali           #+#    #+#              #
#    Updated: 2026/03/26 16:09:59 by fiaudfiz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

DEF_COLOR = \033[0;39m
CYAN    = \033[0;96m
GREEN = \033[0;92m
PURPLE  = \033[0;95m
YELLOW  = \033[0;93m
RED     = \033[0;91m
RESET   = \033[0m

ERR_LOG = .errors.log 

CC = cc
CFLAGS = -O3 -Wall -Werror -Wextra -Wall -I includes -I libft/includes

#Flags commun a tout les modes de debug
DFLAGS_COMMON = -g -Wshadow -fno-omit-frame-pointer

#ASan + UBSan
DFLAGS_ASAN = $(DFLAGS_COMMON) \
			-fsanitize=address,undefined \
			-fno-sanitize-recover=all

#TSan
DFLAGS_TSAN = $(DFLAGS_COMMON) \
				-fsanitize=thread

#Dossiers
SRCS_DIR = srcs/
OBJS_DIR = objs/
HEADER_DIR = includes/

LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a

SRCS_PIPEX = utils.c main.c handle_sons.c struct_init.c handle_error.c
SRCS_BONUS_PIPEX = main_bonus_struct.c utils.c handle_sons.c struct_init_bonus.c handle_error.c here_doc.c

SRCS_MANDATORY_PATH = $(addprefix $(SRCS_DIR), $(SRCS_PIPEX))
SRCS_BONUS_PATH = $(addprefix $(SRCS_DIR), $(SRCS_BONUS_PIPEX))

OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS_MANDATORY_PATH))
OBJS_BONUS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS_BONUS_PATH))

HEADER = $(HEADER_DIR)pipex.h

RM = rm -rf

all: header start_timer $(NAME) end_timer

header:
	@printf "$(YELLOW) Démarrage de la compilation de Pipex...$(RESET)"

start_timer:
	$(eval START_TIME := $(shell date +%s))

debug debug_asan debug_tsan debug_bonus debug_bonus_asan debug_bonus_tsan: \
    CFLAGS = -O0 -Wall -Werror -Wextra -I includes -I libft/includes

#debug classique
debug: DFLAGS = $(DFLAGS_COMMON)
debug: $(LIBFT_LIB) header start_timer $(OBJS) end_timer
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(GREEN) Pipex debug ready !$(DEF_COLOR)"

debug_asan: DFLAGS = $(DFLAGS_ASAN)
debug_asan: $(LIBFT_LIB) header start_timer $(OBJS) end_timer
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(GREEN) Pipex debug [ASan+UBSan] ready !$(DEF_COLOR)"

debug_tsan: DFLAGS = $(DFLAGS_TSAN)
debug_tsan: $(LIBFT_LIB) header start_timer $(OBJS) end_timer
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(YELLOW) Pipex debug [TSan] ready ! $(DEF_COLOR)"

debug_bonus: DFLAGS = $(DFLAGS_COMMON)
debug_bonus: $(LIBFT_LIB) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(GREEN) Pipex bonus debug ready !$(DEF_COLOR)"

debug_bonus_asan: DFLAGS = $(DFLAGS_ASAN)
debug_bonus_asan: $(LIBFT_LIB) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(YELLOW) Pipex bonus debug [ASan+UBSan] ready !$(DEF_COLOR)"

debug_bonus_tsan: DFLAGS = $(DFLAGS_TSAN)
debug_bonus_tsan: $(LIBFT_LIB) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(DFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@printf "$(YELLOW) Pipex bonus debug [TSan] ready !$(DEF_COLOR)"

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_LIB)                                                                       
		@printf "\n\n$(CYAN)8 888888888o    8 8888 8 888888888o   8 8888888888   \`8.\`8888.      ,8'\n"
		@sleep 0.1
		@printf "8 8888    \`88.  8 8888 8 8888    \`88. 8 8888          \`8.\`8888.    ,8'\n"
		@sleep 0.1
		@printf "8 8888     \`88  8 8888 8 8888     \`88 8 8888           \`8.\`8888.  ,8'\n"
		@sleep 0.1
		@printf "8 8888     ,88  8 8888 8 8888     ,88 8 8888            \`8.\`8888.,8'\n"
		@sleep 0.1
		@printf "8 8888.   ,88'  8 8888 8 8888.   ,88' 8 888888888888     \`8.\`88888'\n"
		@sleep 0.1
		@printf "8 888888888P'   8 8888 8 888888888P'  8 8888             .88.\`8888.\n"
		@sleep 0.1
		@printf "8 8888          8 8888 8 8888         8 8888            .8'\`8.\`8888.\n"
		@sleep 0.1
		@printf "8 8888          8 8888 8 8888         8 8888           .8'  \`8.\`8888.\n"
		@sleep 0.1
		@printf "8 8888          8 8888 8 8888         8 8888          .8'    \`8.\`8888.\n"
		@sleep 0.1
		@printf "8 8888          8 8888 8 8888         8 888888888888 .8'      \`8.\`8888.\n$(DEF_COLOR)"
		@rm -f .bonus
		@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)
		@printf "\n\n$(GREEN) Pipex is ready to be used !$(DEF_COLOR)"

bonus : .bonus
	
.bonus: $(OBJS_BONUS) $(LIBFT_LIB)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@touch .bonus
	@printf "\n$(GREEN)✅ Pipex BONUS is ready!$(DEF_COLOR)"
	
TOTAL_FILES := $(words $(SRCS_MANDATORY_PATH))
CURRENT_FILE := 0

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(eval CURRENT_FILE=$(shell printf $$(($(CURRENT_FILE) + 1))))
	@$(eval PERCENT=$(shell printf $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	@printf "\r$(CYAN)🛠️  Compiling Pipex... [%-20s] %d%%" \
		"$(shell printf '#%.0s' $$(seq 1 $$(($(PERCENT) / 5))))" $(PERCENT)
	@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ 2> .temp_err || \
		(printf "\n$(PURPLE)❌ Erreur dans $< :$(RESET)\n" && cat .temp_err >> $(ERR_LOG) && cat .temp_err && rm -f .temp_err)
		

end_timer:
	@$(eval END_TIME := $(shell date +%s))
	@$(eval DURATION := $(shell printf $$(($(END_TIME) - $(START_TIME)))))
	@$(eval ERRORS := $(shell if [ -f $(ERR_LOG) ]; then grep -c "error:" $(ERR_LOG); else printf 0; fi))
	@printf "\n%s\n" "--------------------------------------------------"
	@if [ $(ERRORS) -eq 0 ]; then \
		printf "$(GREEN)✅ COMPILATION TERMINÉE !\n$(RESET)"; \
	else \
		printf "$(RED)❌ COMPILATION TERMINÉE AVEC DES ERREURS\n$(RESET)"; \
	fi
	@printf "Temps écoulé : $(DURATION) secondes\n"
	@printf "  Nombre d'erreurs : $(ERRORS)\n"
	@printf "%s\n" "--------------------------------------------------"
	@rm -f $(ERR_LOG)

clean:
	$(RM) $(OBJS_DIR)
	@make clean -C $(LIBFT_DIR)
	@printf "$(PURPLE) Objects cleaned!$(DEF_COLOR)\n"

fclean: clean
		$(RM) $(NAME) .bonus
		@make fclean -C $(LIBFT_DIR)
		@printf "$(PURPLE) $(NAME) deleted!$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re debug debug_asan debug_tsan debug_bonus debug_bonus_tsan debug_bonus_asan bonus