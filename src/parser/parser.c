/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:25:26 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:55 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "../libft/libft.h"
#include <stdio.h>

char	*find_next_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

int	check_map_info(char *line, t_datas *big_data)
{
	char	**info;

	info = ft_split(line, ' ');
	if (info[2])
		return (1);
	if (ft_strlen(info[0]) == 1)
	{
		if (ft_strncmp(info[0], "C", 1) && ft_strncmp(info[0], "F", 1))
			return (1);
		fill_data(big_data, info);
	}
	else if (ft_strlen(info[0]) == 2)
	{
		if (ft_strncmp(info[0], "SO", 2) && ft_strncmp(info[0], "WE", 2)
			&& ft_strncmp(info[0], "NO", 2) && ft_strncmp(info[0], "EA", 2))
			return (1);
		fill_data(big_data, info);
	}
	else
		return (1);
	return (0);
}

int	check_fl_line(char *line)
{
	int	i;

	i = -1;
	if (!line)
		return (1);
	while (line[++i] != '\n')
		if (line[i] != '1' && line[i] != ' ')
			return (1);
	return (0);
}

int	check_around(char *prev_line, char *line, char *next_line, int i)
{
	if (((line[i + 1] != '1') && (line[i + 1] != ' '))
		|| ((prev_line[i] != '1') && (prev_line[i] != ' '))
		|| ((prev_line[i + 1] != '1') && (prev_line[i + 1] != ' '))
		|| ((next_line[i] != '1') && (next_line[i] != ' '))
		|| ((next_line[i + 1] != '1') && (next_line[i + 1] != ' ')))
		return (1);
	if (i)
	{
		if (((line[i - 1] != '1') && (line[i - 1] != ' '))
			|| ((prev_line[i - 1] != '1') && (prev_line[i - 1] != ' '))
			|| ((next_line[i - 1] != '1') && (next_line[i - 1] != ' ')))
			return (1);
	}
	return (0);
}

int	**parse_map(char *path, t_datas *big_data)
{
	int	fd;
	int	**map;

	map = NULL;
	if (ft_strncmp(path + (ft_strlen(path) - 4), ".cub", 5))
	{
		printf("Please provide a .cub file map.\n");
		return (NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		print_error(path, errno);
		return (NULL);
	}
	if (check_map(fd, big_data))
	{
		printf("Map error.\n");
		exit(1);
	}
	close (fd);
	map = get_map(path, big_data);
	return (map);
}
