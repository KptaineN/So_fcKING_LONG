NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

LIBFT_DIR = includes/LIBFT
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = includes/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

RM = rm -f
MAKE_LIBFT = $(MAKE) -C $(LIBFT_DIR)
MAKE_MLX   = $(MAKE) -C $(MLX_DIR)

# Liste des sources dans le dossier src/
SRC = \
	source/main/main.c \
	source/main/arg_check/arg_check.c \
	source/initialisation/game_init.c \
	source/initialisation/read_map.c \
	source/initialisation/valide_map.c \
	source/initialisation/checking_validation.c \
	source/initialisation/texture/load_texture.c \
	source/start_game/start_game.c \
	source/start_game/player_mouv/player_mouvement.c \
	source/start_game/rendu/render_game.c \
	source/start_game/rendu/render_util.c \
	source/utile/error_util.c \
	source/utile/map_util.c \


OBJS = $(SRC:%.c=%.o)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@echo "🔧 Compilation de LIBFT..."
	$(MAKE_LIBFT)

$(MLX):
	@echo "🔧 Compilation de MiniLibX..."
	$(MAKE_MLX)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "🔧 Compilation de so_long..."
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🗑️ Suppression des fichiers objets..."
	$(RM) $(OBJS)
	$(MAKE_LIBFT) clean || true
	$(MAKE_MLX) clean || true

fclean: clean
	@echo "🗑️ Suppression de $(NAME) et des bibliothèques..."
	$(RM) $(NAME)
	$(MAKE_LIBFT) fclean || true
	# MiniLibX n'a peut-être pas de cible fclean, on l'ignore :
	# $(MAKE_MLX) fclean || true

re: fclean all
