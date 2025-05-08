/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:56:32 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:49:13 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_m/so_long.h"

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

void	free_game_textures(t_game *game)
{
	if (!game || !game->mlx)
		return ;
	if (game->mlx)
	{
		if (game->img_wall)
			mlx_destroy_image(game->mlx, game->img_wall);
		if (game->img_floor)
			mlx_destroy_image(game->mlx, game->img_floor);
		if (game->img_collectible)
			mlx_destroy_image(game->mlx, game->img_collectible);
		if (game->img_exit_close)
			mlx_destroy_image(game->mlx, game->img_exit_close);
		if (game->img_player)
			mlx_destroy_image(game->mlx, game->img_player);
	}
}

void	free_resources(t_game *game)
{
	if (game->grid)
	{
		ft_free(game->grid, game->rows);
		game->grid = NULL;
	}
	free_game_textures(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
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
