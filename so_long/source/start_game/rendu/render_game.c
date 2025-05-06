/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:51:12 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/06 12:50:34 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/so_long.h"

static void	setup_cell_render(t_cell_render *cr, t_cell_setup_params p)
{
	cr->game = p.game;
	cr->buffer_img = p.buffer_img;
	cr->texture = p.texture;
	cr->row = p.pos.y;
	cr->col = p.pos.x;
}

static void	render_cell(t_cell_render *cr)
{
	t_render_info	info;

	info.buffer_img = cr->buffer_img;
	info.texture = cr->texture;
	info.tex_width = cr->game->tile_size;
	info.tex_height = cr->game->tile_size;
	info.x_offset = cr->col * cr->game->tile_size;
	info.y_offset = cr->row * cr->game->tile_size;
	info.mlx = cr->game->mlx;
	draw_texture(&info);
}

static void	*get_texture_for_cell(t_game *game, char cell)
{
	if (cell == WALL)
		return (game->img_wall);
	if (cell == EMPTY)
		return (game->img_floor);
	if (cell == COLLECTIBLE)
		return (game->img_collectible);
	if (cell == EXIT)
	{
		if (game->collectibles == 0)
			return (game->img_exit_open);
		return (game->img_exit_close);
	}
	if (cell == PLAYER)
		return (game->player_frames[game->current_frame]);
	return (NULL);
}

static void	render_tile(t_game *game, void *buffer_img, t_cell_render *cr,
		t_point pos)
{
	t_cell_setup_params	p;
	void				*texture;

	texture = get_texture_for_cell(game, game->grid[pos.y][pos.x]);
	if (!texture)
		return ;
	p.game = game;
	p.buffer_img = buffer_img;
	p.texture = texture;
	p.pos = pos;
	setup_cell_render(cr, p);
	render_cell(cr);
}

void	draw_grid(t_game *game, void *buffer_img)
{
	int				row;
	int				col;
	t_cell_render	cr;
	t_point			pos;

	row = 0;
	while (row < game->rows)
	{
		col = 0;
		while (col < game->cols)
		{
			pos = (t_point){col, row};
			render_tile(game, buffer_img, &cr, pos);
			col++;
		}
		row++;
	}
}
