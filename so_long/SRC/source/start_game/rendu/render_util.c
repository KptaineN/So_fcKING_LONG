/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:57:52 by nkiefer           #+#    #+#             */
/*   Updated: 2025/05/08 19:14:33 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/Header_m/so_long.h"

static void	copy_pixel_data(char *tex_data, char *buff_data, int tex_index,
		int buff_index)
{
	int	color;

	color = 0;
	ft_memcpy(&color, tex_data + tex_index, sizeof(int));
	ft_memcpy(buff_data + buff_index, (const char *)&color, sizeof(int));
}

static void	draw_texture_row(const t_render_info *info)
{
	int	x;
	int	y;
	int	tex_index;
	int	buff_index;

	tex_index = 0;
	buff_index = 0;
	y = 0;
	while (y < info->tex_height)
	{
		x = 0;
		while (x < info->tex_width)
		{
			tex_index = y * info->line_len_tex + x * (info->bpp_tex / 8);
			buff_index = (y + info->y_offset) * info->line_len_buff + (x
					+ info->x_offset) * (info->bpp_buff / 8);
			copy_pixel_data(info->tex_data, info->buff_data, tex_index,
				buff_index);
			x++;
		}
		y++;
	}
}

void	draw_texture(t_render_info *info)
{
	int	endian;

	endian = 0;
	info->buff_data = mlx_get_data_addr(info->buffer_img, &info->bpp_buff,
			&info->line_len_buff, &endian);
	info->tex_data = mlx_get_data_addr(info->texture, &info->bpp_tex,
			&info->line_len_tex, &endian);
	draw_texture_row(info);
}
