/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hadd <hel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:06:52 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/06/28 12:06:54 by hel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int press(int keycode, t_tazi_data *data)
{
    if(keycode == 123)
        data->p.rot = -1;
    if(keycode == 124)
        data->p.rot = 1;
    if(keycode == 13 || keycode == 126) //w
        data->p.dir = 1;
    if(keycode == 1 || keycode == 125)//s
        data->p.dir = -1;
    // if(keycode == 0) //a
    // {
    // }
    // if(keycode == 2)//d
    // {
    // }
    return 0;
}
int release(int keycode, t_tazi_data *data)
{
    if(keycode == 123)
        data->p.rot = 0;
    if(keycode == 124)
        data->p.rot = 0;
    if(keycode == 13 || keycode == 126) //w
        data->p.dir = 0;
    if(keycode == 1 || keycode == 125)//s
        data->p.dir = 0;
    // if(keycode == 0) //a
    // {
    // }
    // if(keycode == 2)//d
    // {
    // }
    return 0;
}

void move(t_tazi_data *data)
{
    double del_x;
    double del_y;

    del_x = cos(data->p.a) * 3 * data->p.dir;
    del_y = sin(data->p.a) * 3 * data->p.dir;

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