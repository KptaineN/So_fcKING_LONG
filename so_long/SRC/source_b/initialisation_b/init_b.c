/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:03:38 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:15:46 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

void	init_images(t_game *game)
{
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_collectible = NULL;
	game->img_exit_close = NULL;
	game->img_exit_open = NULL;
	game->img_enemy = NULL;
	game->img_lava = NULL;
	game->img_magma = NULL;
}

void	init_player(t_game *game)
{
	int	i;

	game->player_x = 0;
	game->player_y = 0;
	game->move_count = 0;
	i = 0;
	while (i < 8)
	{
		game->player_frames[i] = NULL;
		i++;
	}
}

void	init_enemies(t_game *game)
{
	game->enemies = NULL;
	game->num_enemies = 0;
	game->enemy_timer = 0;
	game->delayed_enemies = NULL;
	game->delayed_count = 0;
	game->enemies_spawned = 0;
}

void	init_game_state(t_game *game)
{
	game->grid = NULL;
	game->mlx = NULL;
	game->win = NULL;
	game->current_frame = 0;
	game->animation_timer = 0;
	game->exit_flag = 0;
	game->collectibles = 0;
	game->tile_size = TILE_SIZE;
}

void	init_default_values(t_game *game)
{
	init_game_state(game);
	init_images(game);
	init_player(game);
	if (game->num_enemies > 0)
	{
		place_enemies(game);
	}
	game->should_exit = 0;
}
