/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:02:35 by nkiefer           #+#    #+#             */
/*   Updated: 2025/03/03 17:50:42 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static int	check_char(char c, int *playerCount, int *exitCount,
		int *collectibleCount)
{
	if (!ft_strchr("01CEP", c))
	{
		ft_printf("Erreur: Caractère invalide '%c' détecté dans la map.\n", c);
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

void	validate_player(int player_found)
{
	if (player_found != 1)
	{
		write(2, "Erreur: La map doit contenir exactement un joueur.\n", 52);
		exit(EXIT_FAILURE);
	}
}

void	validate_exit(int exit_found)
{
	if (exit_found != 1)
	{
		write(2, "Erreur: La map doit contenir exactement une sortie.\n", 53);
		exit(EXIT_FAILURE);
	}
}

void	validate_collectible(int collectible_found)
{
	if (collectible_found < 1)
	{
		write(2, "Erreur: La map doit contenir au moins un collectible.\n", 55);
		exit(EXIT_FAILURE);
	}
}
