/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 08:22:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/03/07 15:01:29 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

static void	load_texture(t_game *game, char *path, void **img,
		char *error_message)
{
	int	width;
	int	height;

	*img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!*img)
	{
		perror(error_message);
		free_resources(game);
		exit(EXIT_FAILURE);
	}
}

static void	load_player_frames(t_game *game)
{
	char	path[64];
	char	*num;
	int		i;

	i = 0;
	while (i < 8)
	{
		num = ft_itoa(i);
		if (!num)
		{
			perror("Erreur : échec de ft_itoa");
			free_resources(game);
			exit(EXIT_FAILURE);
		}
		path[0] = '\0';
		ft_strlcat(path, "assets/player/p", sizeof(path));
		ft_strlcat(path, num, sizeof(path));
		ft_strlcat(path, ".xpm", sizeof(path));
		free(num);
		load_texture(game, path, (void **)&game->player_frames[i],
			"Erreur chargement frame player");
		i++;
	}
}

void	load_textures(t_game *game)
{
	load_texture(game, "assets/wall/wall.xpm", (void **)&game->img_wall,
		"Erreur de chargement de l'image des murs");
	load_texture(game, "assets/floor/floor.xpm", (void **)&game->img_floor,
		"Erreur de chargement de l'image du sol");
	load_texture(game, "assets/collect/collect.xpm",
		(void **)&game->img_collectible,
		"Erreur de chargement de l'image des collectibles");
	load_texture(game, "assets/exit/close/exitc.xpm",
		(void **)&game->img_exit_close,
		"Erreur de chargement de l'image de la sortie");
	load_texture(game, "assets/exit/open/exito.xpm",
		(void **)&game->img_exit_open,
		"Erreur de chargement de l'image de la sortie ouverte");
	load_player_frames(game);
}
