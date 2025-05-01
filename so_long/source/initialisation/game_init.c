/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:20:34 by nkiefer           #+#    #+#             */
/*   Updated: 2025/03/04 18:08:23 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	init_default_values(t_game *game)
{
	int	i;

	game->grid = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->current_frame = 0;
	game->animation_timer = 0;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_collectible = NULL;
	game->img_exit_close = NULL;
	game->img_exit_open = NULL;
	game->exit_flag = 0;
	game->collectibles = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->tile_size = TILE_SIZE;
	game->move_count = 0;
	i = 0;
	while (i < 8)
	{
		game->player_frames[i] = NULL;
		i++;
	}
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("Erreur: mlx_init a échoué");
		exit(EXIT_FAILURE);
	}
}

void	load_and_validate_map(t_game *game, char *map_path)
{
	read_map(map_path, game);
	if (!validate_map(game))
	{
		write(2, "Erreur: La map est invalide.\n", 30);
		free_resources(game);
		exit(EXIT_FAILURE);
	}
}

void	init_window(t_game *game)
{
	game->tile_size = TILE_SIZE;
	game->win = mlx_new_window(game->mlx, game->cols * game->tile_size,
			game->rows * game->tile_size, "so_long");
	if (!game->win)
	{
		perror("Erreur: mlx_new_window a échoué");
		free_resources(game);
		exit(EXIT_FAILURE);
	}
}

void	init_game(t_game *game, char *map_path)
{
	init_default_values(game);
	init_mlx(game);
	load_and_validate_map(game, map_path);
	init_window(game);
}
