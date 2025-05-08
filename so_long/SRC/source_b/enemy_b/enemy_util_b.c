/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_util_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:53:44 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:15:13 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

void	count_enemies(t_game *game)
{
	int	i;
	int	j;

	game->num_enemies = 0;
	i = -1;
	while (++i < game->rows)
	{
		j = -1;
		while (++j < game->cols)
			if (game->grid[i][j] == ENEMY)
				game->num_enemies++;
	}
}

void	game_over(t_game *game)
{
	if (game && game->mlx)
	{
		ft_printf("💀 Game Over.\n");
		exit_game(game);
	}
}

void	free_enemies(t_game *game)
{
	if (game->enemies)
	{
		free(game->enemies);
		game->enemies = NULL;
	}
	if (game->delayed_enemies)
	{
		free(game->delayed_enemies);
		game->delayed_enemies = NULL;
	}
}

void	update_enemy_glide(t_game *game, t_enemy *e)
{
	int	next_x;

	next_x = e->spawn_x + e->glide_dir;
	if (next_x >= 0 && next_x < game->cols
		&& is_walkable(game->grid[e->spawn_y][next_x]))
	{
		e->spawn_x = next_x;
	}
	else
	{
		e->glide_dir *= -1;
	}
}

void	spawn_enemies_when_ready(t_game *game)
{
	int	i;

	if (game->collectibles == 0 && game->enemies_spawned == 0)
	{
		game->enemies = malloc(sizeof(t_enemy) * game->delayed_count);
		if (!game->enemies)
			return ;
		i = 0;
		while (i < game->delayed_count)
		{
			game->enemies[i] = game->delayed_enemies[i];
			i++;
		}
		game->num_enemies = game->delayed_count;
		game->enemies_spawned = 1;
		free(game->delayed_enemies);
		game->delayed_enemies = NULL;
		ft_printf("✅ Ennemis transférés avec succès (count: %d)\n",
			game->num_enemies);
	}
}
