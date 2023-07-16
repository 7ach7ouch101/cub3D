/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:06:52 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/07/16 04:30:58 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	limit_angles(double ra)
{
	if (ra > (2 * M_PI))
		ra = ra - (2 * M_PI);
	if (ra < 0)
		ra = (2 * M_PI) + ra;
	return (ra);
}

int	press(int keycode, t_tazi_data *data)
{
	if (keycode == 53)
	{
		mlx_destroy_window(data->mlx.mlx_p, data->mlx.mlx_w);
		exit(0);
	}
	if (keycode == 123)
		data->p.rot = -1;
	if (keycode == 124)
		data->p.rot = 1;
	if (keycode == 13 || keycode == 126) //w
		data->p.dir = 1;
	if (keycode == 1 || keycode == 125)//s
		data->p.dir = -1;
	if (keycode == 0) //a
		data->p.dir = 2;
	if (keycode == 2)//d
		data->p.dir = 3;
	return 0;
}
int release(int keycode, t_tazi_data *data)
{
	if (keycode == 123)
		data->p.rot = 0;
	if (keycode == 124)
		data->p.rot = 0;
	if (keycode == 13 || keycode == 126) //w
		data->p.dir = 0;
	if (keycode == 1 || keycode == 125)//s
		data->p.dir = 0;
	if(keycode == 0) //a
		data->p.dir = 0;
	if(keycode == 2)//d
		data->p.dir = 0;
	return 0;
}

void move(t_tazi_data *data)
{
	double del_x;
	double del_y;

	del_x = cos(data->p.a) * 3 * data->p.dir;
	del_y = sin(data->p.a) * 3 * data->p.dir;

	if(data->p.dir == 2)
	{
		del_x = cos(limit_angles(data->p.a - M_PI/2)) * 1.5 * data->p.dir;
		del_y = sin(limit_angles(data->p.a - M_PI/2)) * 1.5 * data->p.dir;
	}
	else if(data->p.dir == 3)
	{
		del_x = cos(limit_angles(data->p.a + M_PI/2)) * 1.5 * data->p.dir;
		del_y = sin(limit_angles(data->p.a + M_PI/2)) * 1.5 * data->p.dir;
	}
	if(data->map[(int)((data->p.y + del_y) / BLOCK_SIZE)][(int)((data->p.x + del_x) / BLOCK_SIZE)] != '1')
	{
		data->p.x += del_x;
		data->p.y += del_y;
	}
}

void rotate(t_tazi_data *data)
{
	data->p.a += (0.1 * data->p.rot);
}