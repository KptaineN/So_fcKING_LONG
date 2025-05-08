/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:00:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:52:22 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_m/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (arg_check(argc, argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	init_game(&game, argv[1]);
	if (game.valid)
	{
		start_game_loop(&game);
		free_resources(&game);
	}
	return (0);
}

int	exit_game(t_game *game)
{
	mlx_loop_end(game->mlx);
	return (0);
}
