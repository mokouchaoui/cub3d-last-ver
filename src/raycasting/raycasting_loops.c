/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:06:43 by tbraquem          #+#    #+#             */
/*   Updated: 2022/06/14 11:37:04 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_dof_vline(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	while (ray->dof < find_dof(data))
	{
		ray->map_x = (int)(ray->ray_x) >> 6;
		ray->map_y = (int)(ray->ray_y) >> 6;
		if ((ray->map_x < data->vars_game->longest_line
				&& ray->map_y < data->vars_game->nb_line)
			&& (ray->map_x >= 0 && ray->map_y >= 0)
			&& data->vars_game->map[ray->map_y][ray->map_x] == 1)
		{
			ray->hx = ray->ray_x;
			ray->hy = ray->ray_y;
			ray->dis_h = dist(data->vars_game->player_x,
					data->vars_game->player_y, ray->hx, ray->hy);
			ray->dof = find_dof(data);
		}
		else
		{
			ray->ray_x += ray->x_off;
			ray->ray_y += ray->y_off;
			ray->dof++;
		}
	}
}

void	loop_dof_vline_hline(t_datas *data)
{
	t_raycast	*ray;

	ray = data->raycast;
	while (ray->dof < find_dof(data))
	{
		ray->map_x = (int)(ray->ray_x) >> 6;
		ray->map_y = (int)(ray->ray_y) >> 6;
		if ((ray->map_x < data->vars_game->longest_line
				&& ray->map_y < data->vars_game->nb_line)
			&& (ray->map_x >= 0 && ray->map_y >= 0)
			&& data->vars_game->map[ray->map_y][ray->map_x] == 1)
		{
			ray->vx = ray->ray_x;
			ray->vy = ray->ray_y;
			ray->dis_v = dist(data->vars_game->player_x,
					data->vars_game->player_y, ray->vx, ray->vy);
			ray->dof = find_dof(data);
		}
		else
		{
			ray->ray_x += ray->x_off;
			ray->ray_y += ray->y_off;
			ray->dof++;
		}
	}
}
