/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:00:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/03/03 17:50:42 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (arg_check(argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	init_game(&game, argv[1]);
	load_textures(&game);
	start_game_loop(&game);
	free_resources(&game);
	return (EXIT_SUCCESS);
}

int	exit_game(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}
