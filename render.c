/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 00:24:29 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/07/16 04:56:02 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

unsigned int get_color(t_tazi_data *data, int x, int y, int wall_h)
{
    unsigned int 	color;
    int     tx;
    int     ty;
    char	*texture;

    if (!data->ray[x].bol)
	{
		if (data->ray[x].a < (3 * M_PI / 2) && data->ray[x].a > M_PI / 2)
		    texture = data->param[2];//we;
		else
			texture = data->param[3];//ea;
		tx = (int)data->ray[x].y % BLOCK_SIZE;
		ty = ((y - ((WIN_HEIGHT / 2) - (wall_h / 2))))
			* ((double)(double)BLOCK_SIZE / (double)wall_h);
	}
	else
	{
		if (data->ray[x].a < M_PI && data->ray[x].a > 0)
			texture = data->param[1];//so
		else
			texture = data->param[0];//no
		tx = (int)data->ray[x].x % BLOCK_SIZE;
		ty = ((y - ((WIN_HEIGHT / 2) - (wall_h / 2))))
			* ((double)(double)BLOCK_SIZE / (double)wall_h);
	}
    //puts("kheloooo\n");
    //data->textur11.img = mlx_xpm_file_to_image(data->mlx.mlx_p, texture, &demn, &demn);
    // data->textur11.addr = mlx_get_data_addr(data->textur11.img, &data->textur11.bits_per_pixel, &data->textur11.line_length, &data->textur11.endian);
   // puts("khe\n");
	color = *(unsigned int *)((data->textur11.addr + (ty * data->textur11.line_length + tx * (data->textur11.bits_per_pixel / 8))));
	return color;
}



void  lfonc_likatrsam(t_tazi_data *data, int wall_h, int x)
{
    int y;
    unsigned int color;
    
    y = 0;
    while(y < (WIN_HEIGHT / 2 - wall_h / 2))
    {
        my_mlx_pixel_put(&(data->render), x, y, data->c);
        y++;
    }
    while(y < (WIN_HEIGHT / 2 + wall_h / 2))
    {
       color = get_color(data, x, y, wall_h);
       //puts("naiiii\n");
        my_mlx_pixel_put(&(data->render), x, y , color);
        y++;
    }
    while(y < WIN_HEIGHT)
    {
        my_mlx_pixel_put(&(data->render), x, y, data->f);
        y++;
    }

	// int	start;
	// int	end;
	// int	index;

	// start = (WIN_HEIGHT / 2) - wall_h / 2;
	// end = (WIN_HEIGHT / 2) + wall_h / 2;
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
	// mlx_clear_window(data->mlx.mlx_p, data->mlx.mlx_w);
    // mlx_destroy_image(data->mlx.mlx_p, data->render.img);
    data->render.img = mlx_new_image(data->mlx.mlx_p, 1024, 720);
    data->render.addr = mlx_get_data_addr(data->render.img, &data->render.bits_per_pixel, &data->render.line_length, &data->render.endian);
    int dem = BLOCK_SIZE;
    data->textur11.img = mlx_xpm_file_to_image(data->mlx.mlx_p, "texture.xpm", &dem, &dem);
        data->textur11.addr = mlx_get_data_addr(data->textur11.img, &data->textur11.bits_per_pixel, &data->textur11.line_length, &data->textur11.endian);

    move(data);
    rotate(data);
    cast_ray(data);
    draw_all(data);
    
	mlx_put_image_to_window(data->mlx.mlx_p, data->mlx.mlx_w, data->render.img,0,0);
    return 0;
}


void    mlx_func(t_tazi_data *data)
{
    mlx_hook(data->mlx.mlx_w, 2, 0, press, data);
	mlx_hook(data->mlx.mlx_w, 3, 0, release, data);

    // data->render.img = mlx_new_image(data->mlx.mlx_p, 1024, 720);
    // data->render.addr = mlx_get_data_addr(data->render.img, &data->render.bits_per_pixel, &data->render.line_length, &data->render.endian);

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