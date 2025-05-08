/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_util_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:56:32 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:16:57 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

void	ft_free(char **array, int count)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_player_frames(void *mlx, void **frames)
{
	int	i;

	i = 0;
	if (!frames)
		return ;
	while (i < 8)
	{
		if (frames[i])
			mlx_destroy_image(mlx, frames[i]);
		i++;
	}
}

void	free_game_textures(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->img_exit_close)
		mlx_destroy_image(game->mlx, game->img_exit_close);
	if (game->img_exit_open)
		mlx_destroy_image(game->mlx, game->img_exit_open);
	if (game->img_enemy)
		mlx_destroy_image(game->mlx, game->img_enemy);
	if (game->img_lava)
		mlx_destroy_image(game->mlx, game->img_lava);
	if (game->img_magma)
		mlx_destroy_image(game->mlx, game->img_magma);
}

void	free_resources(t_game *game)
{
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->img_enemy)
	{
		mlx_destroy_image(game->mlx, game->img_enemy);
		game->img_enemy = NULL;
	}
	free_player_frames(game->mlx, (void **)game->player_frames);
	free_game_textures(game);
	if (game->grid)
		ft_free(game->grid, game->rows);
	free_enemies(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

void	handle_error(char *message, char **map, int rows, int fd)
{
	if (fd >= 0)
		close(fd);
	if (map)
		ft_free(map, rows);
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE);
}
