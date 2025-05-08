/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 08:22:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:14:09 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/Header_m/so_long.h"

static void	load_texture(t_game *game, char *path, void **img,
		char *error_message)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!*img)
	{
		perror(error_message);
		free_resources(game);
		exit(EXIT_FAILURE);
	}
}

void	load_textures(t_game *game)
{
	load_texture(game, "assets/wall/wall.xpm", (void **)&game->img_wall,
		"Error\nloading the wall image");
	load_texture(game, "assets/floor/floor.xpm", (void **)&game->img_floor,
		"Error\nloading the floor image");
	load_texture(game, "assets/collect/collect.xpm",
		(void **)&game->img_collectible,
		"Error\nloading the collectible image");
	load_texture(game, "assets/exit/close/exitc.xpm",
		(void **)&game->img_exit_close, "Error\nloading the closed exit image");
	load_texture(game, "assets/player/p0.xpm", (void **)&game->img_player,
		"Error\nloading the player image");
}
