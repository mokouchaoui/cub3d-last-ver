/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokoucha <mokoucha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:24:26 by mokoucha          #+#    #+#             */
/*   Updated: 2022/11/09 01:41:43 by mokoucha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pixel_put(t_img_data *img_data, int x, int y, int color)
{
	char	*dst;

	if (y >= WIN_H || x >= WIN_W)
		return ;
	if (y < 0 || x < 0)
		return ;
	dst = img_data->addr + (y * img_data->line_length + x
			* (img_data->bpp / 8));
	*(unsigned int *) dst = color;
}
