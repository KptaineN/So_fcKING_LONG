/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:00:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:16:15 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

void	close_game(t_game *game)
{
	free_resources(game);
	exit(EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (arg_check(argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	init_game(&game, argv[1]);
	load_textures(&game);
	start_game_loop(&game);
	free_resources(&game);
	return (0);
}

int	exit_game(t_game *game)
{
	if (game && game->mlx && !game->should_exit)
	{
		game->should_exit = 1;
		mlx_loop_end(game->mlx);
	}
	return (0);
}
