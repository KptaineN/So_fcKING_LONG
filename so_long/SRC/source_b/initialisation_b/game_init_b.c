/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 19:20:34 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:15:41 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

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
	if (!validate_map(game))
	{
		write(2, "Error\nmap is not valide.\n", 30);
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
	count_enemies(game);
	place_enemies(game);
	init_window(game);
}
