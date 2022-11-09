/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:05:01 by tbraquem          #+#    #+#             */
/*   Updated: 2022/06/14 11:41:08 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_angle(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	ray->ray_angle = data->vars_game->player_angle - (DR * 30);
	if (ray->ray_angle < 0)
		ray->ray_angle += (2 * M_PI);
	if (ray->ray_angle > (2 * M_PI))
		ray->ray_angle -= (2 * M_PI);
}

void	get_ray_direction(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	if (ray->ray_angle > M_PI)
	{
		ray->ray_y = (((int)data->vars_game->player_y >> 6) << 6) - 0.0001;
		ray->ray_x = (data->vars_game->player_y - ray->ray_y)
			* ray->a_tan + data->vars_game->player_x;
		ray->y_off = -SQUARE_SIZE;
		ray->x_off = -ray->y_off * ray->a_tan;
	}
	if (ray->ray_angle < M_PI)
	{
		ray->ray_y = (((int)data->vars_game->player_y >> 6) << 6) + SQUARE_SIZE;
		ray->ray_x = (data->vars_game->player_y - ray->ray_y)
			* ray->a_tan + data->vars_game->player_x;
		ray->y_off = SQUARE_SIZE;
		ray->x_off = -ray->y_off * ray->a_tan;
	}
	if (ray->ray_angle == 0 || ray->ray_angle == M_PI)
	{
		ray->ray_x = data->vars_game->player_x;
		ray->ray_y = data->vars_game->player_y;
		ray->dof = find_dof(data);
	}
}

static void	get_ca(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	ray->ca = data->vars_game->player_angle - ray->ray_angle;
	if (ray->ca < 0)
		ray->ca += (2 * M_PI);
	if (ray->ca > (2 * M_PI))
		ray->ca -= (2 * M_PI);
	ray->distance = ray->distance * cos(ray->ca);
}

void	get_distance(t_datas *data, int *nb_ray)
{
	t_raycast	*ray;

	ray = data->raycast;
	if (ray->dis_v < ray->dis_h)
	{
		ray->shade = 0.5;
		ray->ray_x = ray->vx;
		ray->ray_y = ray->vy;
		ray->distance = ray->dis_v;
		if ((int)ray->distance <= 0)
			ray->distance = 15.0;
		ray->side = 0;
	}
	(*nb_ray)++;
	if (ray->dis_h < ray->dis_v)
	{
		ray->ray_x = ray->hx;
		ray->ray_y = ray->hy;
		ray->distance = ray->dis_h;
		if ((int)ray->distance <= 0)
			ray->distance = 15.0;
		ray->side = 1;
	}
	get_ca(data);
}

void	get_ray_direction_vline(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	if (ray->ray_angle > M_PI / 2 && ray->ray_angle < (3 * M_PI) / 2)
	{
		ray->ray_x = (((int)data->vars_game->player_x >> 6) << 6) - 0.0001;
		ray->ray_y = (data->vars_game->player_x - ray->ray_x)
			* ray->n_tan + data->vars_game->player_y;
		ray->x_off = -SQUARE_SIZE;
		ray->y_off = -ray->x_off * ray->n_tan;
	}
	if (ray->ray_angle < M_PI / 2 || ray->ray_angle > (3 * M_PI) / 2)
	{
		ray->ray_x = (((int)data->vars_game->player_x >> 6) << 6) + SQUARE_SIZE;
		ray->ray_y = (data->vars_game->player_x - ray->ray_x)
			* ray->n_tan + data->vars_game->player_y;
		ray->x_off = SQUARE_SIZE;
		ray->y_off = -ray->x_off * ray->n_tan;
	}
	if (ray->ray_angle == 0 || ray->ray_angle == M_PI)
	{
		ray->ray_x = data->vars_game->player_x;
		ray->ray_y = data->vars_game->player_y;
		ray->dof = find_dof(data);
	}
}
