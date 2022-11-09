/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:25:33 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/01 08:25:35 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_camera_left(t_datas *data)
{
	data->vars_game->player_angle -= 0.1;
	if (data->vars_game->player_angle < 0)
		data->vars_game->player_angle += 2 * M_PI;
	data->vars_game->player_dx = cos(data->vars_game->player_angle) * 5;
	data->vars_game->player_dy = sin(data->vars_game->player_angle) * 5;
}

void	player_camera_right(t_datas *data)
{
	data->vars_game->player_angle += 0.1;
	if (data->vars_game->player_angle > 2 * M_PI)
		data->vars_game->player_angle -= 2 * M_PI;
	data->vars_game->player_dx = cos(data->vars_game->player_angle) * 5;
	data->vars_game->player_dy = sin(data->vars_game->player_angle) * 5;
}
