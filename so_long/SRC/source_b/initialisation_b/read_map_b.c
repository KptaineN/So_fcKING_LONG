/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:01:50 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:15:52 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/Header_b/so_long.h"

int	is_rectangular(char **map, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		if ((int)ft_strlen(map[i]) != cols)
			return (0);
		i++;
	}
	return (1);
}

char	**append_line(char **temp, char *line, int *count, int fd)
{
	char	**new_temp;
	int		i;

	i = 0;
	new_temp = malloc(sizeof(char *) * (*count + 2));
	if (!new_temp)
		handle_error("Error\n malloc", temp, *count, fd);
	while (i < *count)
	{
		new_temp[i] = temp[i];
		i++;
	}
	new_temp[*count] = line;
	new_temp[*count + 1] = NULL;
	free(temp);
	(*count)++;
	return (new_temp);
}

char	**read_lines(int fd, int *count)
{
	char	*line;
	char	**temp;
	size_t	len;

	temp = NULL;
	*count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		len = ft_strlen(line);
		if (len == 0 || line[0] == '\n')
		{
			free(line);
			handle_error("Error\nLigne empty detected", temp, *count, fd);
		}
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		temp = append_line(temp, line, count, fd);
		line = get_next_line(fd);
	}
	return (temp);
}

void	read_map(const char *filename, t_game *game)
{
	int		fd;
	int		count;
	char	**temp;

	fd = -1;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error("Error\ntry to open file", NULL, 0, -1);
	count = 0;
	temp = read_lines(fd, &count);
	close(fd);
	if (count == 0 || temp == NULL)
		handle_error("Error\nMap empty or illisible.", temp, count, -1);
	game->rows = count;
	game->cols = ft_strlen(temp[0]);
	if (!is_rectangular(temp, game->rows, game->cols))
		handle_error("Error\nMap not rectangulare.", temp, count,
			-1);
	game->grid = temp;
	init_enemies(game);
}
