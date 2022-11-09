/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:25:02 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:51 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map(int fd, t_datas *big_data)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = find_next_line(fd);
		if (!line)
			return (1);
		if (check_map_info(line, big_data))
			return (1);
		free(line);
		i++;
	}
	if (check_map_content(fd, big_data))
		return (1);
	return (0);
}

int	loop_check(char *line, char *prev_line, char *next_line, int i)
{
	while (line[i] != '\n')
	{
		if (line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != '0' && line[i] != '1'
			&& line[i] != ' ')
			return (1);
		if (line[i] == ' ')
			if (check_around(prev_line, line, next_line, i))
				return (1);
		i++;
	}
	return (0);
}

int	check_map_characters(char *line, char *prev_line, char *next_line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
	{
		if (check_around(prev_line, line, next_line, i))
			return (1);
		i++;
	}
	if (line[i++] != '1')
		return (1);
	if (loop_check(line, prev_line, next_line, i))
		return (1);
	if (line[i - 1] != '1')
		return (1);
	if (check_corner(prev_line, line, next_line))
		return (1);
	return (0);
}

int	check_map_content(int fd, t_datas *big_data)
{
	char	*prev_line;
	char	*line;
	char	*next_line;
	int		checker;

	big_data->vars_game->nb_line = 1;
	prev_line = find_next_line(fd);
	if (check_fl_line(prev_line))
		return (1);
	line = get_next_line(fd);
	next_line = get_next_line(fd);
	big_data->vars_game->longest_line = ft_strlen(prev_line) - 1;
	while (line)
	{
		if (check_map_characters(line, prev_line, next_line) == 1)
			return (1);
		get_lines(&line, &prev_line, &next_line, fd);
		(big_data->vars_game->nb_line)++;
		checker = get_data(big_data, next_line, line);
		if (checker == 1)
			return (1);
		else if (checker == 0)
			break ;
	}
	return (free_lines(prev_line, next_line, line));
}

int	check_corner(char *prev_line, char *line, char *next_line)
{
	unsigned int	i;

	i = 0;
	if (ft_strlen(line) > ft_strlen(prev_line))
	{
		while (i < (ft_strlen(line) - ft_strlen(prev_line) - 1))
		{
			if (line[i + ft_strlen(prev_line)] != '1')
				return (1);
			i++;
		}
	}
	else if (ft_strlen(line) > ft_strlen(next_line))
	{
		while (i < (ft_strlen(line) - ft_strlen(next_line) - 1))
		{
			if (line[i + ft_strlen(next_line)] != '1')
				return (1);
			i++;
		}
	}
	return (0);
}
