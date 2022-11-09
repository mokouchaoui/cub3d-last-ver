/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:25:19 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:54 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_lines(char **line, char **prev_line, char **next_line, int fd)
{
	if (*prev_line)
		free(*prev_line);
	*prev_line = *line;
	*line = *next_line;
	*next_line = get_next_line(fd);
}

int	get_data(t_datas *big_data, char *next_line, char *line)
{
	if (!next_line)
	{
		if ((int)ft_strlen(line) > big_data->vars_game->longest_line)
			big_data->vars_game->longest_line = ft_strlen(line) - 1;
		(big_data->vars_game->nb_line)++;
		if (check_fl_line(line))
			return (1);
		else
			return (0);
	}
	if ((int)ft_strlen(line) > big_data->vars_game->longest_line)
		big_data->vars_game->longest_line = ft_strlen(line) - 1;
	return (3);
}

void	get_player_info(int i, int j, char c, t_datas *big_data)
{
	big_data->vars_game->player_x = j * SQUARE_SIZE;
	big_data->vars_game->player_y = i * SQUARE_SIZE;
	if (c == 'N')
		big_data->vars_game->player_angle = degtorad(NORTH);
	if (c == 'S')
		big_data->vars_game->player_angle = degtorad(SOUTH);
	if (c == 'W')
		big_data->vars_game->player_angle = degtorad(WEST);
	if (c == 'E')
		big_data->vars_game->player_angle = degtorad(EAST);
	big_data->vars_game->player_dx = cos(big_data->vars_game->player_angle) * 5;
	big_data->vars_game->player_dy = sin(big_data->vars_game->player_angle) * 5;
	big_data->vars_game->found_player = 1;
}
