/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:24:34 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:46 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_line(t_datas *data, int x, int color)
{
	int		pixels;
	float	pixel_x;
	float	pixel_y;

	pixels = data->raycast->end_y - data->raycast->begin_y;
	pixel_x = x;
	pixel_y = data->raycast->begin_y;
	while (pixels)
	{
		pixel_put(data->img_data, pixel_x, pixel_y, color);
		pixel_y++;
		pixels--;
	}
}

void	draw_square(t_datas *data, int x, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			pixel_put(data->img_data, x + i, data->raycast->begin_y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_rectangle(t_datas *data, int x, int color)
{
	int	i;

	if (x < 0 || x > WIN_W)
		return ;
	if (data->raycast->end_y <= 0 || data->raycast->begin_y >= WIN_H)
		return ;
	i = 0;
	while (i < 8)
	{
		if ((x + i) < 0 || (x + i) > WIN_W)
			break ;
		draw_line(data, x + i, color);
		i++;
	}
}

void	draw_walls(t_datas *data, int y, int nb_ray)
{
	int			out;
	t_raycast	*ray;

	out = 0;
	ray = data->raycast;
	if (ray->side)
	{
		if ((data->vars_game->player_y - ray->ray_y) < 0)
			out = get_wall_color(data, &data->vars_game->tex_east);
		else
			out = get_wall_color(data, &data->vars_game->tex_north);
	}
	else
	{
		if ((data->vars_game->player_x - ray->ray_x) < 0)
			out = get_wall_color(data, &data->vars_game->tex_south);
		else
			out = get_wall_color(data, &data->vars_game->tex_west);
	}
	data->raycast->begin_y = y + ray->line_off;
	draw_square(data, nb_ray * 8, 8, out);
	ray->ty += ray->ty_step;
}

void	draw(t_datas *data, int nb_ray)
{
	t_raycast	*ray;
	int			y;

	ray = data->raycast;
	y = 0;
	while (y < ray->line_h)
	{
		draw_walls(data, y, nb_ray);
		y++;
	}
	data->raycast->begin_y = 0;
	data->raycast->end_y = ((WIN_H - ray->line_h) / 2);
	draw_rectangle(data, nb_ray * 8, data->vars_game->sky_color);
	data->raycast->begin_y = (WIN_H - ray->line_h) / 2 + ray->line_h;
	data->raycast->end_y = WIN_H;
	draw_rectangle(data, nb_ray * 8, data->vars_game->floor_color);
}
