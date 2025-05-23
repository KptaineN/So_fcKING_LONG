/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:01:30 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 20:13:59 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_m/so_long.h"

int	check_walls(t_game *game)
{
	if (!check_wall_rows(game))
		return (0);
	if (!check_wall_columns(game))
		return (0);
	return (1);
}

static int	validate_accessibility(t_game *game, t_floodtrack *track)
{
	if (track->count_c == game->collectibles && track->found_exit)
		return (1);
	ft_printf("Error\nNot acces to collectibles or exit.\n");
	return (0);
}

int	check_accessibility(t_game *game)
{
	char			**map_copy;
	t_floodtrack	flood_track;

	flood_track.count_c = 0;
	flood_track.found_exit = 0;
	flood_track.start.x = game->player_x;
	flood_track.start.y = game->player_y;
	map_copy = copy_map(game->grid, game->rows, game->cols);
	if (!map_copy)
		return (ft_printf("Error\nFail map copy.\n"), 0);
	if (game->player_x < 0 || game->player_x >= game->cols || game->player_y < 0
		|| game->player_y >= game->rows)
		handle_error("Position de départ invalide.", game->grid, game->rows,
			-1);
	ft_floodfill(game, map_copy, &flood_track);
	ft_free(map_copy, game->rows);
	return (validate_accessibility(game, &flood_track));
}

int	validate_map(t_game *game)
{
	t_map_validation	validate;

	if (!game->grid)
		return (ft_printf("Error\nMap empty.\n"), 0);
	validate.player_count = 0;
	validate.exit_count = 0;
	validate.collectible_count = 0;
	count_elements(game, &validate.player_count, &validate.exit_count,
		&validate.collectible_count);
	if (!validate_player(validate.player_count))
		return (0);
	if (!validate_exit(validate.exit_count))
		return (0);
	if (!validate_collectible(validate.collectible_count))
		return (0);
	if (!check_walls(game))
		return (0);
	if (!check_accessibility(game))
		return (0);
	return (1);
}
