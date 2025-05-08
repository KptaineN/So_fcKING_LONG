/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:59:00 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 20:32:02 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_m/so_long.h"

int	check_wall_rows(t_game *game)
{
	int	j;

	if (!game->grid[0] || !game->grid[game->rows - 1])
		return (ft_printf("Error\nWall rows not properly allocated.\n"), 0);
	j = 0;
	while (j < game->cols)
	{
		if (game->grid[0][j] != WALL || game->grid[game->rows - 1][j] != WALL)
		{
			ft_printf("Error\nMap bad wall build from top and down\n");
			return (0);
		}
		j++;
	}
	return (1);
}

int	check_wall_columns(t_game *game)
{
	int	a;

	a = 0;
	while (a < game->rows)
	{
		if (!game->grid[a])
		{
			ft_printf("Error\nWall column not properly allocated.\n");
			return (0);
		}
		if (game->grid[a][game->cols - 1] != WALL || game->grid[a][0] != WALL)
		{
			ft_printf("Error\n Map bad wall build from left and right.\n");
			return (0);
		}
		a++;
	}
	return (1);
}

static void	ft_fill(t_game *game, char **map, t_point pos, t_floodtrack *track)
{
	if (pos.x < 0 || pos.x >= game->cols || pos.y < 0 || pos.y >= game->rows)
		return ;
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'v')
		return ;
	if (map[pos.y][pos.x] == COLLECTIBLE)
		track->count_c++;
	if (map[pos.y][pos.x] == 'E')
	{
		track->found_exit = 1;
		return ;
	}
	map[pos.y][pos.x] = 'v';
	ft_fill(game, map, (t_point){pos.x + 1, pos.y}, track);
	ft_fill(game, map, (t_point){pos.x - 1, pos.y}, track);
	ft_fill(game, map, (t_point){pos.x, pos.y + 1}, track);
	ft_fill(game, map, (t_point){pos.x, pos.y - 1}, track);
}

void	ft_floodfill(t_game *game, char **map, t_floodtrack *track)
{
	t_point	start;

	start.x = track->start.x;
	start.y = track->start.y;
	track->count_c = 0;
	track->found_exit = 0;
	ft_fill(game, map, start, track);
}

char	**copy_map(char **grid, int rows, int cols)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	copy = NULL;
	copy = malloc(sizeof(char *) * rows);
	if (!copy)
		return (NULL);
	while (i < rows)
	{
		copy[i] = malloc(sizeof(char) * (cols + 1));
		if (!copy[i])
		{
			j = 0;
			while (j < i)
				free(copy[j++]);
			free(copy);
			return (NULL);
		}
		ft_strlcpy(copy[i], grid[i], cols + 1);
		i++;
	}
	return (copy);
}
