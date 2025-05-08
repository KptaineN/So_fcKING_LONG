NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = includes/LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

RM = rm -f
MAKE_LIBFT = $(MAKE) -C $(LIBFT_DIR)
MAKE_MLX   = $(MAKE) -C $(MLX_DIR)

# Fichiers obligatoires
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

# Fichiers bonus
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

# Objets
OBJS_M = $(SRC_MANDATORY:.c=.o)
OBJS_B = $(SRC_BONUS:.c=.o)

# Règles principales
m: fclean $(NAME)

b: fclean bonus

$(NAME): $(LIBFT) $(MLX) $(OBJS_M)
	@echo "🔧 Compilation mandatory → $(NAME)"
	$(CC) $(CFLAGS) $(OBJS_M) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

bonus: $(LIBFT) $(MLX) $(OBJS_B)
	@echo "✨ Compilation bonus → $(NAME)"
	$(CC) $(CFLAGS) $(OBJS_B) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE_LIBFT)

$(MLX):
	$(MAKE_MLX)

clean:
	@echo "🧹 Suppression des fichiers objets..."
	$(RM) $(OBJS_M) $(OBJS_B)
	$(MAKE_LIBFT) clean || true
	$(MAKE_MLX) clean || true

fclean: clean
	@echo "🗑️ Suppression de l’exécutable..."
	$(RM) $(NAME)
	$(MAKE_LIBFT) fclean || true

re: fclean m

.PHONY: m b bonus clean fclean re
