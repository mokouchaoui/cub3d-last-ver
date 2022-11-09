/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:35:54 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:43:39 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define WIN_W 512
# define WIN_H 512
# define SQUARE_SIZE 64
# define DR 0.0174533
# define MAP_W 10 // NOTE: To delete
# define MAP_H 10 // NOTE: To delete.
# include "../libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>

enum	e_direction
{
	NORTH = 270,
	SOUTH = 90,
	WEST = 180,
	EAST = 0
};

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		heigth;
	int		width;
}				t_img_data;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
}				t_mlx_data;

typedef struct s_raycast
{
	int		dof;
	int		map_x;
	int		map_y;
	int		line_off;
	int		side;
	float	ray_x;
	int		begin_y;
	int		end_y;
	float	ray_y;
	float	x_off;
	float	y_off;
	float	ray_angle;
	float	a_tan;
	float	n_tan;
	float	distance;
	float	dis_h;
	float	hx;
	float	hy;
	float	dis_v;
	float	vx;
	float	vy;
	float	shade;
	float	line_h;
	float	ty_off;
	float	ty_step;
	float	ty;
	float	tx;
	float	ca;
}				t_raycast;

typedef struct s_vars_game
{
	float		player_x;
	float		player_y;
	float		player_dx;
	float		player_dy;
	double		player_angle;
	int			longest_line;
	int			nb_line;
	int			**map;
	char		*ceil_c;
	char		*floor_c;
	char		*south_path;
	char		*north_path;
	char		*east_path;
	char		*west_path;
	t_img_data	tex_north;
	t_img_data	tex_south;
	t_img_data	tex_west;
	t_img_data	tex_east;
	int			sky_color;
	int			floor_color;
	int			found_player;
}				t_vars_game;

typedef struct s_datas
{
	struct s_img_data	*img_data;
	struct s_mlx_data	*mlx_data;
	struct s_raycast	*raycast;
	struct s_vars_game	*vars_game;
}				t_datas;

char		*get_next_line(int fd);

// Utils
void		print_error(char *message, int num_error);
void		remove_nl(char *string);

// Free
void		free_2d(char **array);
void		free_int_2d(int **array, int size);
int			destroy_all(t_datas *data);
int			destroy_all(t_datas *data);
int			free_lines(char *prev_line, char *next_line, char *line);

// Utils math
int			radtodeg(float rad);
int			rgb_to_hex(int r, int g, int b);
int			get_hex_from_str(char *str);
int			convert(signed char sc);
float		degtorad(int deg);
float		degtorad(int deg);

// Draw
void		draw_square(t_datas *data, int x, int size, int color);
void		draw_rectangle(t_datas *data, int x, int color);
void		draw(t_datas *data, int nb_ray);
void		pixel_put(t_img_data *img_data, int x, int y, int color);
void		clear_screen(t_datas *big_data);

// Raycasting
void		get_angle(t_datas *data);
void		get_ray_direction(t_datas *data);
void		get_ray_direction_vline(t_datas *data);
void		get_distance(t_datas *data, int *nb_ray);
void		loop_dof_vline(t_datas *data);
void		loop_dof_vline_hline(t_datas *data);
void		texture_shade(t_datas *data);
void		update_ray_angle(t_datas *data);
void		vh_variable_init(t_datas *data, int choice);
void		line_height_init(t_datas *data);
void		cast_rays(t_datas *data);
int			find_dof(t_datas *data);
int			get_wall_color(t_datas *data, t_img_data *tex);
float		dist(float ax, float ay, float bx, float by);

// Player
void		player_up(t_datas *data);
void		player_down(t_datas *data);
void		player_left(t_datas *data);
void		player_right(t_datas *data);

// Camera
void		player_camera_left(t_datas *data);
void		player_camera_right(t_datas *data);

// Textures
void		load_all_textures(t_datas *data);
t_img_data	load_texture(t_datas *data, t_img_data *ret, char *path);

// Parser
int			check_map(int fd, t_datas *big_data);
int			loop_check(char *line, char *prev_line, char *next_line, int i);
int			check_map_characters(char *line, char *prev_line, char *next_line);
int			check_map_content(int fd, t_datas *big_data);
int			check_corner(char *prev_line, char *line, char *next_line);
int			get_data(t_datas *big_data, char *next_line, char *line);
int			check_map_info(char *line, t_datas *big_data);
int			check_fl_line(char *line);
int			check_around(char *prev_line, char *line, char *next_line, int i);
int			**parse_map(char *path, t_datas *big_data);
int			**get_map(char *path, t_datas *big_data);
void		fill_data(t_datas *big_data, char **info);
void		get_lines(char **line, char **prev_line, char **next_line, int fd);
char		*find_next_line(int fd);
void		get_player_info(int i, int j, char c, t_datas *big_data);

#endif
