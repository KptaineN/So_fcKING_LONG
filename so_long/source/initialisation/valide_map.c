/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:01:30 by nkiefer           #+#    #+#             */
/*   Updated: 2025/03/03 17:50:42 by nkiefer          ###   ########.fr       */
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
	int		count_c;
	char	**map_copy;
	t_point	start;

	start.x = game->player_x;
	start.y = game->player_y;
	count_c = 0;
	map_copy = copy_map(game->grid, game->rows, game->cols);
	if (!map_copy)
	{
		ft_printf("Erreur : Échec de la copie de la map.\n");
		return (0);
	}
	ft_floodfill(game, map_copy, start, &count_c);
	ft_printf("Collectibles trouvés : %d/%d\n", count_c, game->collectibles);
	ft_free(map_copy, game->rows);
	if (count_c == game->collectibles)
		return (1);
	ft_printf("Erreur : La sortie n'est pas accessible depuis le joueur.\n");
	return (0);
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
	validate_player(player_count);
	validate_exit(exit_count);
	validate_collectible(collectible_count);
	if (!check_walls(game))
		return (0);
	if (!check_accessibility(game))
	{
		ft_printf("Erreur: La sortie n'est pas accessible depuis le joueur.\n");
		return (0);
	}
	return (1);
}
