/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mouvement_b.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:45:27 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:17:18 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/Header_b/so_long.h"

void	check_enemy_collision(t_game *game, int x, int y)
{
	int	i;

	if (!game->enemies)
		return ;
	i = 0;
	while (i < game->num_enemies)
	{
		if (game->enemies[i].x == x && game->enemies[i].y == y)
			game_over(game);
		i++;
	}
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->grid[game->player_y][game->player_x] = EMPTY;
	game->player_x = new_x;
	game->player_y = new_y;
	game->grid[new_y][new_x] = PLAYER;
	check_enemy_collision(game, new_x, new_y);
}

static void	handle_player_interaction(t_game *game, int new_x, int new_y)
{
	if (game->grid[new_y][new_x] == EXIT)
	{
		if (game->collectibles == 0)
		{
			ft_printf("Congratulations! You found the exit!\n");
			exit_game(game);
		}
		else
			ft_printf("You still have %d collectibles to collect.\n",
				game->collectibles);
		return ;
	}
	if (game->grid[new_y][new_x] == COLLECTIBLE)
	{
		game->collectibles--;
		game->grid[new_y][new_x] = EMPTY;
		ft_printf("Collectible collected! %d remaining\n", game->collectibles);
	}
	check_enemy_collision(game, new_x, new_y);
}

static void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (new_x < 0 || new_x >= game->cols || new_y < 0 || new_y >= game->rows
		|| game->grid[new_y][new_x] == WALL)
		return ;
	handle_player_interaction(game, new_x, new_y);
	if (game->grid[new_y][new_x] == EXIT && game->collectibles > 0)
		return ;
	update_player_position(game, new_x, new_y);
	game->move_count++;
	ft_printf("Numbre of mouvements : %d\n", game->move_count);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		move_player(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		move_player(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		move_player(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		move_player(game, 1, 0);
	else if (keycode == KEY_ESC)
		exit_game(game);
	return (0);
}
