/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:01:30 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/05 18:23:49 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"


int	check_walls(t_game *game)
{
	int	j;
	int	a;

	j = 0;
	while (j < game->cols)
	{
		if (game->grid[0][j] != WALL || game->grid[game->rows - 1][j] != WALL)
		{
			ft_printf("Erreur: map mal muré de haut en bas\n");
			return (0);
		}
		j++;
	}
	a = 0;
	while (a < game->rows)
	{
		if (game->grid[a][0] != WALL || game->grid[a][game->cols - 1] != WALL)
		{
			ft_printf("Erreur: map mal muré de gauche a droite.\n");
			return (0);
		}
		a++;
	}
	return (1);
}
int	check_accessibility(t_game *game)
{
	char			**map_copy;
	t_point			start;
	t_floodtrack	track;

	start.x = game->player_x;
	start.y = game->player_y;
	track.count_c = 0;
	track.found_exit = 0;

	map_copy = copy_map(game->grid, game->rows, game->cols);
	if (!map_copy)
	{
		ft_printf("Erreur : échec de la copie de la map.\n");
		return (0);
	}

	ft_floodfill(game, map_copy, start, &track);
	ft_free(map_copy, game->rows);

	if (track.count_c != game->collectibles)
	{
		ft_printf("Erreur : %d collectible(s) pas accessible(s).\n",
			game->collectibles - track.count_c);
		return (0);
	}
	if (!track.found_exit)
	{
		ft_printf("Erreur : La sortie est inaccessible depuis le joueur.\n");
		return (0);
	}
	return (1);
}
int	validate_map(t_game *game)
{
	int	player_count;
	int	exit_count;
	int	collectible_count;

	if (!game->grid)
	{
		ft_printf("Erreur: La map est vide.\n");
		return (0);
	}
	player_count = 0;
	exit_count = 0;
	collectible_count = 0;
	count_elements(game, &player_count, &exit_count, &collectible_count);

	if (!validate_player(player_count))
		return (0);
	if (!validate_exit(exit_count))
		return (0);
	if (!validate_collectible(collectible_count))
		return (0);
	if (!check_walls(game))
		return (0);
	if (!check_accessibility(game))
	{
		ft_printf("Erreur: La sortie ou les collectibles ne sont pas accessibles depuis le joueur.\n");
		return (0);
	}
	return (1);
}
