/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:00:00 by nkiefer           #+#    #+#             */
/*   Updated: 2025/03/03 17:50:42 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

void	check_open_file(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Erreur: Impossible d'ouvrir le fichier %s.\n", arg);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	arg_check(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Erreur: Nombre d'arguments incorrect.\n");
		ft_printf("Usage: %s <map_file.ber>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (ft_strlen(argv[1]) < 5)
	{
		ft_printf("Erreur: Le nom du fichier est trop court.\n");
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
	{
		ft_printf("Erreur: Le fichier doit avoir l'extension .ber.\n");
		return (EXIT_FAILURE);
	}
	check_open_file(argv[1]);
	return (EXIT_SUCCESS);
}
