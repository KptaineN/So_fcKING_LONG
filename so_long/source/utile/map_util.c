/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:59:00 by nkiefer           #+#    #+#             */
/*   Updated: 2025/03/07 14:52:23 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	ft_fill(t_game *game, char **map, t_point pos, int *count_c)
{
	if (pos.x < 0 || pos.x >= game->cols || pos.y < 0 || pos.y >= game->rows)
		return ;
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'E'
		|| map[pos.y][pos.x] == 'v')
		return ;
	if (map[pos.y][pos.x] == COLLECTIBLE)
		(*count_c)++;
	map[pos.y][pos.x] = 'v';
	ft_fill(game, map, (t_point){pos.x + 1, pos.y}, count_c);
	ft_fill(game, map, (t_point){pos.x - 1, pos.y}, count_c);
	ft_fill(game, map, (t_point){pos.x, pos.y + 1}, count_c);
	ft_fill(game, map, (t_point){pos.x, pos.y - 1}, count_c);
}

void	ft_floodfill(t_game *game, char **map, t_point start, int *count_c)
{
	ft_fill(game, map, start, count_c);
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
