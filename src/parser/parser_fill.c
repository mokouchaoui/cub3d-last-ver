/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:25:13 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:53 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_data(t_datas *big_data, char **info)
{
	if (!ft_strncmp(info[0], "C", 1))
		big_data->vars_game->ceil_c = ft_strdup(info[1]);
	else if (!ft_strncmp(info[0], "F", 1))
		big_data->vars_game->floor_c = ft_strdup(info[1]);
	if (!ft_strncmp(info[0], "SO", 2))
		big_data->vars_game->south_path = ft_strdup(info[1]);
	if (!ft_strncmp(info[0], "NO", 2))
		big_data->vars_game->north_path = ft_strdup(info[1]);
	if (!ft_strncmp(info[0], "WE", 2))
		big_data->vars_game->west_path = ft_strdup(info[1]);
	if (!ft_strncmp(info[0], "EA", 2))
		big_data->vars_game->east_path = ft_strdup(info[1]);
	free_2d(info);
}
