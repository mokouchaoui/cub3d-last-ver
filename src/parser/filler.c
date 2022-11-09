/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:24:51 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:50 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	**malloc_map(t_datas *big_data)
{
	int		**map;
	int		i;

	i = 0;
	map = (int **)malloc((sizeof(int *) * big_data->vars_game->nb_line));
	if (!map)
		return (NULL);
	while (i < big_data->vars_game->nb_line)
	{
		map[i] = (int *)malloc((sizeof(int)
					* big_data->vars_game->longest_line));
		if (!map[i])
			return (NULL);
		i++;
	}
	return (map);
}

char	*find_first_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line[0] != '1' && line[0] != ' ')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static void	fill_map(t_datas *big_data, char *line, int **map, int i)
{
	int	j;

	j = 0;
	while (line[j] != '\n')
	{
		if (line[j] == '0' || line[j] == ' ')
			map[i][j] = 0;
		else if (line[j] == '1')
			map[i][j] = 1;
		else
		{
			map[i][j] = 0;
			get_player_info(i, j, line[j], big_data);
		}
		j++;
	}
	while (j < big_data->vars_game->longest_line)
		map[i][j++] = 0;
}

void	transform_map(t_datas *big_data, char *line, int **map, int fd)
{
	int		i;

	i = 0;
	while (i < big_data->vars_game->nb_line)
	{
		fill_map(big_data, line, map, i);
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

int	**get_map(char *path, t_datas *big_data)
{
	int		**map;
	char	*line;
	int		fd;

	big_data->vars_game->found_player = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc_map(big_data);
	if (!map)
		return (NULL);
	line = find_first_line(fd);
	transform_map(big_data, line, map, fd);
	if (big_data->vars_game->found_player == 0)
	{
		printf("Map error: No player found!\n");
		exit(1);
	}
	return (map);
}
