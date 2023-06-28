/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hadd <hel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:24:29 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/06/28 12:19:41 by hel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void  lfonc_likatrsam(t_tazi_data *data, int wall_h, int x)
{
    int y;
    
    y = 0;
    while(y < (WIN_HEIGHT / 2 - wall_h / 2))
    {
        my_mlx_pixel_put(&(data->render), x, y, 0x000fff);
        y++;
    }
     while(y < (WIN_HEIGHT / 2 + wall_h / 2))
    {
        my_mlx_pixel_put(&(data->render), x, y, 0x00ff00);
        y++;
    }
    while(y < WIN_HEIGHT)
    {
        my_mlx_pixel_put(&(data->render), x, y, 0xffffff);
        y++;
    }
    
}

void draw_all(t_tazi_data *data)
{
    int i;

    i = 0;
    while (i < WN_WIDTH)
    {
        lfonc_likatrsam(data, BLOCK_SIZE / data->ray[i].dist * l3iba , i);
        i++;
    }
    
}

int rendering(t_tazi_data *data)
{
	mlx_clear_window(data->mlx.mlx_p, data->mlx.mlx_w);
    mlx_destroy_image(data->mlx.mlx_p, data->render.img);
    data->render.img = mlx_new_image(data->mlx.mlx_p, 1024, 720);
    data->render.addr = mlx_get_data_addr(data->render.img, &data->render.bits_per_pixel, &data->render.line_length, &data->render.endian);
    move(data);
    rotate(data);
    cast_ray(data);
    draw_all(data);
    
	mlx_put_image_to_window(data->mlx.mlx_p, data->mlx.mlx_w, data->render.img,0,0);
    return 0;
}

int et(void *i)
{
    exit(0);
}

void    mlx_func(t_tazi_data *data)
{
    mlx_hook(data->mlx.mlx_w, 2, 0, press, data);
	mlx_hook(data->mlx.mlx_w, 3, 0, release, data);
	mlx_hook(data->mlx.mlx_w, 17, 0, et, NULL);

    data->render.img = mlx_new_image(data->mlx.mlx_p, 1024, 720);
    data->render.addr = mlx_get_data_addr(data->render.img, &data->render.bits_per_pixel, &data->render.line_length, &data->render.endian);

	mlx_loop_hook(data->mlx.mlx_p, rendering, data);
}


void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;
    
    if(x < 0 || x >= WN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}