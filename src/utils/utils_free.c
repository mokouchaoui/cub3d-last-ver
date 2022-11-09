/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:35:54 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:42:40 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	free_int_2d(int **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

void	destroy_infos(t_datas *data)
{
	t_vars_game	*v;

	v = data->vars_game;
	free(v->ceil_c);
	free(v->floor_c);
	free(v->south_path);
	free(v->north_path);
	free(v->east_path);
	free(v->west_path);
}

int	free_lines(char *prev_line, char *next_line, char *line)
{
	free(prev_line);
	free(next_line);
	free(line);
	return (0);
}

int	destroy_all(t_datas *data)
{
	destroy_infos(data);
	free_int_2d(data->vars_game->map, data->vars_game->nb_line);
	mlx_destroy_image(data->mlx_data->mlx, data->vars_game->tex_north.img);
	mlx_destroy_image(data->mlx_data->mlx, data->vars_game->tex_south.img);
	mlx_destroy_image(data->mlx_data->mlx, data->vars_game->tex_west.img);
	mlx_destroy_image(data->mlx_data->mlx, data->vars_game->tex_east.img);
	mlx_destroy_image(data->mlx_data->mlx, data->img_data->img);
	mlx_clear_window(data->mlx_data->mlx, data->mlx_data->win);
	mlx_destroy_window(data->mlx_data->mlx, data->mlx_data->win);
	exit(0);
}
