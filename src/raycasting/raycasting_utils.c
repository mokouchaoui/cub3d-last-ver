/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbraquem <tbraquem@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:09:49 by tbraquem          #+#    #+#             */
/*   Updated: 2022/06/14 11:39:22 by tbraquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int	get_wall_color(t_datas *data, t_img_data *tex)
{
	int			pixel;
	int			out;
	t_raycast	*ray;

	ray = data->raycast;
	pixel = (((int)(ray->ty)) * tex->heigth + (int)(ray->tx)) * 4;
	out = (convert(tex->addr[pixel + 2]) << 16)
		| (convert(tex->addr[pixel + 1]) << 8) | (convert(tex->addr[pixel]));
	return (out);
}

int	find_dof(t_datas *data)
{
	if (data->vars_game->nb_line > data->vars_game->longest_line)
		return (data->vars_game->nb_line);
	else
		return (data->vars_game->longest_line);
}
