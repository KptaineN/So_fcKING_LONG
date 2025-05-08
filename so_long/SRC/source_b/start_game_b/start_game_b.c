/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:55:02 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:16:23 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

void	*create_buffer_image(t_game *game)
{
	int		width;
	int		height;
	void	*buffer;

	width = game->cols * game->tile_size;
	height = game->rows * game->tile_size;
	buffer = mlx_new_image(game->mlx, width, height);
	if (!buffer)
		perror("Error\nImpossible to create tampon image");
	return (buffer);
}

void	render_move_count(t_game *game)
{
	char	*nbr_str;

	nbr_str = ft_itoa(game->move_count);
	if (!nbr_str)
	{
		perror("Error\nEchec ft_itoa");
		free_resources(game);
		exit(EXIT_FAILURE);
	}
	mlx_string_put(game->mlx, game->win, 10, 20, 0x000000, nbr_str);
	mlx_string_put(game->mlx, game->win, 11, 21, 0x000000, nbr_str);
	free(nbr_str);
}

int	render_game(t_game *game)
{
	void	*buffer_img;

	buffer_img = create_buffer_image(game);
	if (!buffer_img)
		return (0);
	update_player_animation(game);
	draw_grid(game, buffer_img);
	mlx_put_image_to_window(game->mlx, game->win, buffer_img, 0, 0);
	render_move_count(game);
	mlx_destroy_image(game->mlx, buffer_img);
	mlx_do_sync(game->mlx);
	return (0);
}

int	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_player_animation(game);
	game->enemy_timer++;
	if (game->enemy_timer >= 60)
	{
		spawn_enemies_when_ready(game);
		update_enemies(game);
		game->enemy_timer = 0;
	}
	return (render_game(game));
}

void	start_game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 17, 0, exit_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
