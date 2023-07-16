/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:06:52 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/07/16 08:05:35 by mmeziani         ###   ########.fr       */
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

//13 || 126 = w; 1||125 = s;0=a;2=d
int	press(int keycode, t_tazi_data *data)
{
	if (keycode == 53)
	{
		free_kolchi(data);
		free_map(data);
		mlx_destroy_window(data->mlx.mlx_p, data->mlx.mlx_w);
		exit(0);
	}
	if (keycode == 123)
		data->p.rot = -1;
	if (keycode == 124)
		data->p.rot = 1;
	if (keycode == 13 || keycode == 126)
		data->p.dir = 1;
	if (keycode == 1 || keycode == 125)
		data->p.dir = -1;
	if (keycode == 0)
		data->p.dir = 2;
	if (keycode == 2)
		data->p.dir = 3;
	return (0);
}

int	release(int keycode, t_tazi_data *data)
{
	if (keycode == 123)
		data->p.rot = 0;
	if (keycode == 124)
		data->p.rot = 0;
	if (keycode == 13 || keycode == 126)
		data->p.dir = 0;
	if (keycode == 1 || keycode == 125)
		data->p.dir = 0;
	if (keycode == 0)
		data->p.dir = 0;
	if (keycode == 2)
		data->p.dir = 0;
	return (0);
}

void	move(t_tazi_data *data)
{
	double	del_x;
	double	del_y;

	del_x = cos(data->p.a) * 3.5 * data->p.dir;
	del_y = sin(data->p.a) * 3.5 * data->p.dir;
	if (data->p.dir == 2)
	{
		del_x = cos(limit_angles(data->p.a - M_PI / 2)) * 1.5 * data->p.dir;
		del_y = sin(limit_angles(data->p.a - M_PI / 2)) * 1.5 * data->p.dir;
	}
	else if (data->p.dir == 3)
	{
		del_x = cos(limit_angles(data->p.a + M_PI / 2)) * 1.5 * data->p.dir;
		del_y = sin(limit_angles(data->p.a + M_PI / 2)) * 1.5 * data->p.dir;
	}
	if (data->map[(int)((data->p.y + (10 * del_y)) / BLOCK_SIZE)]
		[(int)((data->p.x + (10 * del_x)) / BLOCK_SIZE)] != '1')
	{
		data->p.x += del_x;
		data->p.y += del_y;
	}
}

void	rotate(t_tazi_data *data)
{
	data->p.a += (0.05 * data->p.rot);
}
