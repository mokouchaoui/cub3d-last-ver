/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:24:07 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:32 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_func(int keycode, void *big_data)
{
	t_datas	*data;

	data = (t_datas *)big_data;
	if (keycode == 53)
		destroy_all(data);
	if (keycode == 123)
		player_camera_left(data);
	if (keycode == 124)
		player_camera_right(data);
	if (keycode == 0)
		player_left(data);
	if (keycode == 2)
		player_right(data);
	if (keycode == 126 || keycode == 13)
		player_up(data);
	if (keycode == 125 || keycode == 1)
		player_down(data);
	clear_screen(data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->win,
		data->img_data->img, 0, 0);
	return (0);
}

void	start_game(t_datas *data)
{
	load_all_textures(data);
	cast_rays(data);
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->win,
		data->img_data->img, 0, 0);
	mlx_hook(data->mlx_data->win, 2, 1L << 0, key_func, data);
	mlx_hook(data->mlx_data->win, 17, 1L << 17, destroy_all, data);
	mlx_loop(data->mlx_data->mlx);
}

int	main(int argc, char **argv)
{
	t_datas		data;
	t_mlx_data	mlx_data;
	t_img_data	img_data;
	t_raycast	raycast;
	t_vars_game	vars_game;

	if (argc < 2)
	{
		printf("Please provide a map file\n");
		exit(1);
	}
	data.mlx_data = &mlx_data;
	data.img_data = &img_data;
	data.raycast = &raycast;
	data.vars_game = &vars_game;
	data.vars_game->map = parse_map(argv[1], &data);
	if (!data.vars_game->map)
		return (1);
	mlx_data.mlx = mlx_init();
	mlx_data.win = mlx_new_window(mlx_data.mlx, WIN_W, WIN_H, "cub3d uwu");
	img_data.img = mlx_new_image(mlx_data.mlx, WIN_W, WIN_H);
	img_data.addr = mlx_get_data_addr(img_data.img, &img_data.bpp,
			&img_data.line_length, &img_data.endian);
	start_game(&data);
	return (0);
}
