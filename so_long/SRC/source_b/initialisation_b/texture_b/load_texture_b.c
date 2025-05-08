/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 08:22:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:15:33 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/Header_b/so_long.h"

void	update_player_animation(t_game *game)
{
	game->animation_timer++;
	if (game->animation_timer >= 10)
	{
		game->current_frame = (game->current_frame + 1) % 8;
		game->animation_timer = 0;
	}
}

static void	load_texture(t_game *game, char *path, void **img,
		char *error_message)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!*img)
	{
		ft_printf("%s (%s)\n", error_message, path);
		perror(error_message);
		free_resources(game);
		exit(EXIT_FAILURE);
	}
}

static void	load_player_frames(t_game *game)
{
	char	path[64];
	char	*num;
	int		i;

	i = 0;
	while (i < 8)
	{
		num = ft_itoa(i);
		if (!num)
		{
			perror("Error\nechec ft_itoa");
			free_resources(game);
			exit(EXIT_FAILURE);
		}
		path[0] = '\0';
		ft_strlcat(path, "assets/player/p", sizeof(path));
		ft_strlcat(path, num, sizeof(path));
		ft_strlcat(path, ".xpm", sizeof(path));
		free(num);
		load_texture(game, path, (void **)&game->player_frames[i],
			"Error\n loading player frame");
		i++;
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
	load_texture(game, "assets/exit/open/exito.xpm",
		(void **)&game->img_exit_open, "Error\nloading the open exit image");
	load_texture(game, "assets/enemy/enemy.xpm", (void **)&game->img_enemy,
		"Error\nloading the enemy image");
	load_texture(game, "assets/wall/.f/lava.xpm", (void **)&game->img_lava,
		"Error\nloading alternative wall image");
	load_texture(game, "assets/floor/.f/magma.xpm", (void **)&game->img_magma,
		"Error\nloading alternative floor image");
	load_player_frames(game);
}
