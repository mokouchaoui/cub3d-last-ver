/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 13:58:26 by tbraquem          #+#    #+#             */
/*   Updated: 2022/06/14 11:38:23 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_shade(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	if (ray->shade == 1)
	{
		ray->tx = (int)(ray->ray_x / 2.0) % 32;
		if (ray->ray_angle > 180)
			ray->tx = 31 - ray->tx;
	}
	else
	{
		ray->tx = (int)(ray->ray_y / 2.0) % 32;
		if (ray->ray_angle > 90 && ray->ray_angle < 270)
			ray->tx = 31 - ray->tx;
	}
}

void	update_ray_angle(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	if (ray->line_h > 320)
	{
		ray->ty_off = (ray->line_h - 320) / 2.0;
		ray->line_h = 320;
	}
	ray->ray_angle += DR;
	if (ray->ray_angle < 0)
		ray->ray_angle += (2 * M_PI);
	if (ray->ray_angle > (2 * M_PI))
		ray->ray_angle -= (2 * M_PI);
}

void	vh_variable_init(t_datas *data, int choice)
{
	t_raycast	*ray;

	ray = data->raycast;
	if (choice == 1)
	{
		ray->dis_h = 1000000;
		ray->hx = data->vars_game->player_x;
		ray->hy = data->vars_game->player_y;
		ray->a_tan = (-1 / tan(ray->ray_angle));
	}
	else if (choice == 2)
	{
		ray->dis_v = 1000000;
		ray->vx = data->vars_game->player_x;
		ray->vy = data->vars_game->player_y;
		ray->n_tan = -tan(ray->ray_angle);
	}
}

void	line_height_init(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	ray->line_h = (SQUARE_SIZE * WIN_H) / ray->distance;
	ray->ty_off = 0;
	ray->line_off = 250 - ((int)ray->line_h >> 1);
	ray->ty_step = 32.0 / (float) ray->line_h;
	ray->ty = ray->ty_off * ray->ty_step;
}

void	cast_rays(t_datas *data)
{
	t_raycast	*ray;
	int			nb_ray;

	ray = data->raycast;
	get_angle(data);
	nb_ray = 0;
	while (nb_ray < 60)
	{
		vh_variable_init(data, 1);
		get_ray_direction(data);
		ray->dof = 0;
		loop_dof_vline(data);
		vh_variable_init(data, 2);
		get_ray_direction_vline(data);
		ray->dof = 0;
		loop_dof_vline_hline(data);
		ray->shade = 1;
		get_distance(data, &nb_ray);
		line_height_init(data);
		texture_shade(data);
		draw(data, nb_ray);
		update_ray_angle(data);
	}
}
