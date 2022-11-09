/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_general.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 15:35:54 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:42:46 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *message, int num_error)
{
	perror(message);
	strerror(num_error);
}

void	remove_nl(char *string)
{
	int		i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '\n')
			string[i] = 0;
		i++;
	}
}

void	clear_screen(t_datas *big_data)
{
	mlx_destroy_image(big_data->mlx_data->mlx, big_data->img_data->img);
	big_data->img_data->img = mlx_new_image(big_data->mlx_data->mlx,
			WIN_W, WIN_H);
}
