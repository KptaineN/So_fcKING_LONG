/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:20:34 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/29 10:28:03 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_m/so_long.h"

void	init_default_values(t_game *game)
{
	game->grid = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_collectible = NULL;
	game->img_exit_close = NULL;
	game->exit_flag = 0;
	game->collectibles = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->tile_size = TILE_SIZE;
	game->move_count = 0;
	game->valid = 0;
}

void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		perror("Error\nmlx_init fail ");
		exit(EXIT_FAILURE);
	}
}

void	load_and_validate_map(t_game *game, char *map_path)
{
	read_map(map_path, game);
	if (!game->grid)
	{
		write(2, "Error\nMap empty or unreadable.\n", 31);
		free_resources(game);
		exit(EXIT_FAILURE);
	}
	if (!validate_map(game))
	{
		write(2, "Error\nmap is not valide.\n", 26);
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
		perror("Error\nmlx_new_window fail");
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
	load_textures(game);
	game->valid = 1;
}
