/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:59:00 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:17:04 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

int	is_walkable(char cell)
{
	return (cell == EMPTY || cell == COLLECTIBLE || cell == PLAYER);
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
		strncpy(copy[i], grid[i], cols);
		copy[i][cols] = '\0';
		i++;
	}
	return (copy);
}
