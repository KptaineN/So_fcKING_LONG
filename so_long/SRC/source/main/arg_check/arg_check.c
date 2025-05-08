/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:00:00 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:13:23 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/Header_m/so_long.h"

void	check_open_file(char *arg)
{
	int	fd;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nFail open file %s.\n", arg);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

int	arg_check(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error\nWrong number of arguments\n");
		ft_printf("Usage: %s <map_file.ber>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (ft_strlen(argv[1]) < 5)
	{
		ft_printf("Error\nFilename too short\n");
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4) != 0)
	{
		ft_printf("Error\nFile must have .ber extension\n");
		return (EXIT_FAILURE);
	}
	check_open_file(argv[1]);
	return (EXIT_SUCCESS);
}
