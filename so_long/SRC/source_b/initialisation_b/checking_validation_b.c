/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_validation_b.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:02:35 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:15:22 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

static int	check_char(char c, int *playerCount, int *exitCount,
		int *collectibleCount)
{
	if (!ft_strchr("01CEPM", c))
	{
		ft_printf("Error\nCharacter not valide '%c' détected in the map.\n", c);
		return (0);
	}
	if (c == PLAYER)
		(*playerCount)++;
	else if (c == EXIT)
		(*exitCount)++;
	else if (c == COLLECTIBLE)
		(*collectibleCount)++;
	return (1);
}

int	count_elements(t_game *game, int *playerCount, int *exitCount,
		int *collectibleCount)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			c = game->grid[i][j];
			if (!check_char(c, playerCount, exitCount, collectibleCount))
				return (0);
			if (c == PLAYER)
			{
				game->player_x = j;
				game->player_y = i;
			}
			j++;
		}
		i++;
	}
	game->collectibles = *collectibleCount;
	return (1);
}

int	validate_player(int player_found)
{
	if (player_found != 1)
	{
		write(2, "Error\nMap need to content exactly one player.\n", 50);
		return (0);
	}
	return (1);
}

int	validate_exit(int exit_found)
{
	if (exit_found != 1)
	{
		write(2, "Error\nMap need to conteny exacly one exit.\n", 50);
		return (0);
	}
	return (1);
}

int	validate_collectible(int collectible_found)
{
	if (collectible_found < 1)
	{
		write(2, "Error\nMap need to content one or more collectible.\n", 54);
		return (0);
	}
	return (1);
}
