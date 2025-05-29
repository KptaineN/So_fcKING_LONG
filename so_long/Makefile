NAME_MANDATORY = so_long
NAME_BONUS     = so_long_bonus

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -Iincludes

# LIBRARIES
LIBFT_DIR = includes/LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

RM = rm -f
MAKE_LIBFT = $(MAKE) -C $(LIBFT_DIR)
MAKE_MLX   = $(MAKE) -C $(MLX_DIR)

# Sources
SRC_MANDATORY = \
	SRC/source/main/main.c \
	SRC/source/main/arg_check/arg_check.c \
	SRC/source/initialisation/game_init.c \
	SRC/source/initialisation/read_map.c \
	SRC/source/initialisation/valide_map.c \
	SRC/source/initialisation/checking_validation.c \
	SRC/source/initialisation/texture/load_texture.c \
	SRC/source/start_game/start_game.c \
	SRC/source/start_game/player_mouv/player_mouvement.c \
	SRC/source/start_game/rendu/render_game.c \
	SRC/source/start_game/rendu/render_util.c \
	SRC/source/utile/error_util.c \
	SRC/source/utile/map_util.c

SRC_BONUS = \
	SRC/source_b/main_b/main_b.c \
	SRC/source_b/main_b/arg_check_b/arg_check_b.c \
	SRC/source_b/initialisation_b/game_init_b.c \
	SRC/source_b/initialisation_b/init_b.c \
	SRC/source_b/initialisation_b/read_map_b.c \
	SRC/source_b/initialisation_b/valide_map_b.c \
	SRC/source_b/initialisation_b/checking_validation_b.c \
	SRC/source_b/initialisation_b/texture_b/load_texture_b.c \
	SRC/source_b/start_game_b/start_game_b.c \
	SRC/source_b/start_game_b/player_mouv_b/player_mouvement_b.c \
	SRC/source_b/start_game_b/rendu_b/render_game_b.c \
	SRC/source_b/start_game_b/rendu_b/render_util_b.c \
	SRC/source_b/utile_b/error_util_b.c \
	SRC/source_b/utile_b/map_util_b.c \
	SRC/source_b/enemy_b/enemy_b.c \
	SRC/source_b/enemy_b/enemy_util_b.c

OBJ_MANDATORY = $(SRC_MANDATORY:.c=.o)
OBJ_BONUS     = $(SRC_BONUS:.c=.o)

BUILD_FLAG = .build_type

all: check_mandatory $(LIBFT) $(MLX) $(NAME_MANDATORY)

b: check_bonus $(LIBFT) $(MLX) $(NAME_BONUS)

check_mandatory:
	@if [ -f $(BUILD_FLAG) ] && grep -q BONUS $(BUILD_FLAG); then \
		echo "\033[31m❌ Currently in BONUS mode. Run 'make fclean' first.\033[0m"; \
		exit 1; \
	fi
	@echo MANDATORY > $(BUILD_FLAG)

check_bonus:
	@if [ -f $(BUILD_FLAG) ] && grep -q MANDATORY $(BUILD_FLAG); then \
		echo "\033[31m❌ Currently in MANDATORY mode. Run 'make fclean' first.\033[0m"; \
		exit 1; \
	fi
	@echo BONUS > $(BUILD_FLAG)

$(NAME_MANDATORY): $(OBJ_MANDATORY)
	$(CC) $(CFLAGS) $^ $(MLX_FLAGS) $(LIBFT_FLAGS) -o $@

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $^ $(MLX_FLAGS) $(LIBFT_FLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE_LIBFT)

$(MLX):
	$(MAKE_MLX)

clean:
	@echo "\033[33m🧹 Cleaning object files...\033[0m"
	$(RM) $(OBJ_MANDATORY) $(OBJ_BONUS)
	$(MAKE_LIBFT) clean || true
	$(MAKE_MLX) clean || true

fclean: clean
	@echo "\033[31m🗑️  Removing executables and flags...\033[0m"
	$(RM) $(NAME_MANDATORY) $(NAME_BONUS) $(BUILD_FLAG)
	$(MAKE_LIBFT) fclean || true

re: fclean all

.PHONY: all b clean fclean re check_mandatory check_bonus
