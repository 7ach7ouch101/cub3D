/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:24:29 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/07/16 08:39:07 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	lfonc_likatrsam(t_tazi_data *data, int wall_h, int x)
{
	int				y;
	unsigned int	color;

	y = 0;
	while (y < (WIN_HEIGHT / 2 - wall_h / 2))
	{
		my_mlx_pixel_put(&(data->render), x, y, data->c);
		y++;
	}
	while (y < (WIN_HEIGHT / 2 + wall_h / 2))
	{
		color = get_color(data, x, y, wall_h);
		my_mlx_pixel_put(&(data->render), x, y, color);
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&(data->render), x, y, data->f);
		y++;
	}
}

void	draw_all(t_tazi_data *data)
{
	int	i;

	i = 0;
	while (i < WN_WIDTH)
	{
		lfonc_likatrsam(data, BLOCK_SIZE / data->ray[i].dist
			* (double)((WN_WIDTH / 2) * tan(FOV)), i);
		i++;
	}
}

void	for_norm_text2(t_tazi_data *data)
{
	int	dem;

	dem = 64;
	data->textur11[2].img = mlx_xpm_file_to_image(data->mlx.mlx_p,
			data->param[2], &dem, &dem);
	if (!data->textur11[2].img)
		ft_error("Error texture in render", data);
	data->textur11[2].addr = mlx_get_data_addr(data->textur11[2].img,
			&data->textur11[2].bits_per_pixel,
			&data->textur11[2].line_length, &data->textur11[2].endian);
	data->textur11[1].img = mlx_xpm_file_to_image(data->mlx.mlx_p,
			data->param[1], &dem, &dem);
	if (!data->textur11[1].img)
		ft_error("Error texture in render", data);
	data->textur11[1].addr = mlx_get_data_addr(data->textur11[1].img,
			&data->textur11[1].bits_per_pixel,
			&data->textur11[1].line_length, &data->textur11[1].endian);
	data->textur11[3].img = mlx_xpm_file_to_image(data->mlx.mlx_p,
			data->param[3], &dem, &dem);
	if (!data->textur11[3].img)
		ft_error("Error texture in render", data);
	data->textur11[3].addr = mlx_get_data_addr(data->textur11[3].img,
			&data->textur11[3].bits_per_pixel,
			&data->textur11[3].line_length, &data->textur11[3].endian);
}

int	rendering(t_tazi_data *data)
{
	int	dem;

	dem = BLOCK_SIZE;
	data->render.img = mlx_new_image(data->mlx.mlx_p, 1024, 720);
	data->render.addr = mlx_get_data_addr(data->render.img,
			&data->render.bits_per_pixel,
			&data->render.line_length, &data->render.endian);
	for_norm_text2(data);
	data->textur11[0].img = mlx_xpm_file_to_image(data->mlx.mlx_p,
			data->param[0], &dem, &dem);
	if (!data->textur11[0].img)
		ft_error("Error texture in render", data);
	data->textur11[0].addr = mlx_get_data_addr(data->textur11[0].img,
			&data->textur11[0].bits_per_pixel,
			&data->textur11[0].line_length, &data->textur11[0].endian);
	move(data);
	rotate(data);
	cast_ray(data);
	draw_all(data);
	mlx_put_image_to_window(data->mlx.mlx_p, data->mlx.mlx_w,
		data->render.img, 0, 0);
	return (0);
}

void	mlx_func(t_tazi_data *data)
{
	mlx_hook(data->mlx.mlx_w, 2, 0, press, data);
	mlx_hook(data->mlx.mlx_w, 3, 0, release, data);
	mlx_loop_hook(data->mlx.mlx_p, rendering, data);
}
