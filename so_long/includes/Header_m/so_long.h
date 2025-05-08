/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:20:30 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 20:02:18 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# include "../LIBFT/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE_SIZE 32

// Définition des caractères utilisés dans la map
# define WALL '1'
# define EMPTY '0'
# define COLLECTIBLE 'C'
# define PLAYER 'P'
# define EXIT 'E'

// Codes de touches
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_ESC 65307

typedef struct s_game
{
	char	**grid;			// La map sous forme de tableau de chaînes
	int		rows;			// Nombre de lignes
	int		cols;			// Nombre de colonnes
	int		player_x;		// Position X du joueur
	int		player_y;		// Position Y du joueur
	int		collectibles;	// Nombre de collectibles restants
	int		exit_flag;		// activé si la sortie est accessible via flood fill
	void	*mlx;
	void	*win;
	void	*img_player;
	void	*img_wall;
	void	*img_floor;
	void	*img_collectible;
	void	*img_exit_close;
	int		tile_size;
	int		move_count;
	int		valid;
}			t_game;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_map_validation
{
	int	player_count;
	int	exit_count;
	int	collectible_count;
}	t_map_validation;

typedef struct s_floodtrack
{
	t_point	start;
	int		count_c;
	int		found_exit;
}			t_floodtrack;

typedef struct s_render_info
{
	// Données de la texture source
	char	*tex_data;
	int		tex_width;
	int		tex_height;
	int		bpp_tex;
	int		line_len_tex;

	// Données de l'image de destination (le buffer)
	char	*buff_data;
	int		bpp_buff;
	int		line_len_buff;

	// Offsets de dessin dans le buffer
	int		x_offset;
	int		y_offset;

	// Références vers les images (MLX)
	void	*texture;
	void	*buffer_img;
	void	*mlx;
}			t_render_info;

typedef struct s_cell_render
{
	t_game	*game;
	void	*buffer_img;
	void	*texture;
	int		row;
	int		col;
}			t_cell_render;

typedef struct s_cell_setup_params
{
	t_game	*game;
	void	*buffer_img;
	void	*texture;
	t_point	pos;
}			t_cell_setup_params;

/* Prototypes */
void		check_open_file(char *arg);
int			arg_check(int argc, char **argv);
// int check_args(int argc, char *argv[]);
void		init_game(t_game *game, char *map_path);
void		init_window(t_game *game);
void		init_default_values(t_game *game);
void		init_mlx(t_game *game);

/*read and valide map*/
void		load_and_validate_map(t_game *game, char *map_path);
void		read_map(const char *filename, t_game *game);
char		**read_lines(int fd, int *count);
int			is_rectangular(char **temp, int rows, int cols);

int			validate_map(t_game *game);
int			check_accessibility(t_game *game);
int			check_walls(t_game *game);

int			validate_collectible(int collectible_found);
int			validate_exit(int exit_found);
int			validate_player(int player_found);
int			count_elements(t_game *game, int *playerCount, int *exitCount,
				int *collectibleCount);

/* chargement des textures */
void		load_textures(t_game *game);

/* start game */

void		start_game_loop(t_game *game);
int			key_press(int keycode, t_game *game);
int			exit_game(t_game *game);

// render
void		*create_buffer_image(t_game *game);
void		update_player_animation(t_game *game);
void		draw_grid(t_game *game, void *buffer_img);
void		draw_texture(t_render_info *info);

/* error util */
void		ft_free(char **array, int count);
void		free_game_textures(t_game *game);
void		free_resources(t_game *game);
void		handle_error(char *message, char **map, int rows, int fd);
/* map util */
char		**copy_map(char **grid, int rows, int cols);
void		ft_floodfill(t_game *game, char **map, t_floodtrack *track);
int			check_wall_columns(t_game *game);
int			check_wall_rows(t_game *game);

#endif
