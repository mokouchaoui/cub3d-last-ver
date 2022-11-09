/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_loader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:24:40 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:47 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img_data	load_texture(t_datas *data, t_img_data *ret, char *path)
{
	t_img_data	tex;
	int			fd;

	remove_nl(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error(path, errno);
		exit(1);
	}
	close(fd);
	tex.img = mlx_xpm_file_to_image(data->mlx_data->mlx, path, &tex.width,
			&tex.heigth);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bpp, &tex.line_length,
			&tex.endian);
	ret = &tex;
	return (*ret);
}

void	load_all_textures(t_datas *data)
{
	data->vars_game->tex_north = load_texture(data, &data->vars_game->tex_north,
			data->vars_game->north_path);
	data->vars_game->tex_south = load_texture(data, &data->vars_game->tex_south,
			data->vars_game->south_path);
	data->vars_game->tex_west = load_texture(data, &data->vars_game->tex_west,
			data->vars_game->west_path);
	data->vars_game->tex_east = load_texture(data, &data->vars_game->tex_east,
			data->vars_game->east_path);
	data->vars_game->sky_color = get_hex_from_str(data->vars_game->ceil_c);
	data->vars_game->floor_color = get_hex_from_str(data->vars_game->floor_c);
}
