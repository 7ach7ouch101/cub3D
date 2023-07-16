/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:24:29 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/07/16 07:51:05 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	for_norm_color(t_tazi_data *data, int *tt, int *tx, int x)
{
	if (!data->ray[x].bol)
	{
		if (data->ray[x].a < (3 * M_PI / 2) && data->ray[x].a > M_PI / 2)
			*tt = 2;
		else
			*tt = 3;
		*tx = (int)data->ray[x].y % BLOCK_SIZE;
	}
	else
	{
		if (data->ray[x].a < M_PI && data->ray[x].a > 0)
			*tt = 1;
		else
			*tt = 0;
		*tx = (int)data->ray[x].x % BLOCK_SIZE;
	}
}

unsigned int	get_color(t_tazi_data *data, int x, int y, int wall_h)
{
	unsigned int	color;
	int				tx;
	int				ty;
	int				tt;

	for_norm_color(data, &tt, &tx, x);
	ty = ((y - ((WIN_HEIGHT / 2) - (wall_h / 2))))
		* ((double)(double)BLOCK_SIZE / (double)wall_h);
	color = *(unsigned int *)((data->textur11[tt].addr
				+ (ty * data->textur11[tt].line_length + tx
					* (data->textur11[tt].bits_per_pixel / 8))));
	return (color);
}
