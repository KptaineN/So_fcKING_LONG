/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:53:35 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 20:26:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

void	calculate_target(t_enemy *e, int *target_x, int *target_y, int step)
{
	int	dx[8];
	int	dy[8];

	dx[0] = 0;
	dx[1] = 0;
	dx[2] = -1;
	dx[3] = 0;
	dx[4] = 0;
	dx[5] = 0;
	dx[6] = 1;
	dx[7] = 0;
	dy[0] = -1;
	dy[1] = 0;
	dy[2] = 0;
	dy[3] = 0;
	dy[4] = 1;
	dy[5] = 0;
	dy[6] = 0;
	dy[7] = 0;
	*target_x = e->spawn_x + dx[step];
	*target_y = e->spawn_y + dy[step];
}

void	move_enemy(t_game *game, t_enemy *e)
{
	int	target_x;
	int	target_y;

	calculate_target(e, &target_x, &target_y, e->step);
	if (target_x >= 0 && target_x < game->cols && target_y >= 0
		&& target_y < game->rows && is_walkable(game->grid[target_y][target_x]))
	{
		e->x = target_x;
		e->y = target_y;
	}
	else
	{
		e->x = e->spawn_x;
		e->y = e->spawn_y;
	}
	e->step = (e->step + 1) % 8;
}

void	update_enemies(t_game *game)
{
	int	i;

	if (!game->enemies || game->num_enemies == 0)
		return ;
	i = 0;
	while (i < game->num_enemies)
	{
		update_enemy_glide(game, &game->enemies[i]);
		move_enemy(game, &game->enemies[i]);
		if (game->enemies[i].x == game->player_x
			&& game->enemies[i].y == game->player_y)
			game_over(game);
		i++;
	}
}

void	place_enemy_at(t_game *game, int i, int j, int *count)
{
	game->delayed_enemies[*count].x = j;
	game->delayed_enemies[*count].y = i;
	game->delayed_enemies[*count].spawn_x = j;
	game->delayed_enemies[*count].spawn_y = i;
	game->delayed_enemies[*count].step = 0;
	game->delayed_enemies[*count].glide_dir = 1;
	game->grid[i][j] = EMPTY;
	(*count)++;
}

void	place_enemies(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	game->delayed_enemies = malloc(sizeof(t_enemy) * game->num_enemies);
	game->delayed_count = game->num_enemies;
	game->num_enemies = 0;
	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->grid[i][j] == ENEMY)
				place_enemy_at(game, i, j, &count);
			j++;
		}
		i++;
	}
}
