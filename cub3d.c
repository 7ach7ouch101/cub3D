/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hadd <hel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 21:39:12 by mmeziani          #+#    #+#             */
/*   Updated: 2023/06/28 05:05:51 by hel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_data(t_tazi_data *data)
{
    data->p.dir = 0;
    data->p.rot = 0;
    data->p.a = 0;
    data->p.x = 0;
    data->p.y = 0;
    data->map_len_max = 0;
    data->map_wei_max = 0;
    data->ray->dist = 0;
    data->ray->a = 0;
    data->ray->x = 0;
    data->ray->y = 0;
    data->render.bits_per_pixel = 0;
    data->render.line_length = 0;
    data->render.endian = 0;
}

int main(int ac, char **av)
{
    t_tazi_data data;
    init_data(&data);

    if(ac == 2)
    {
        if(check_file(av[1]) == 0)
            return (0);
        data.param = parse_param(av[1]);
        parse_map(av[1], &data);
        position_player(&data);
        data.mlx.mlx_p = mlx_init();
	    data.mlx.mlx_w = mlx_new_window(data.mlx.mlx_p, WN_WIDTH, WIN_HEIGHT, "cub3d");
        mlx_func(&data);
        mlx_loop(data.mlx.mlx_p);
    }
    else
        printf("NOT ENOUGH ARGUMENTS !!\n");
    return (0);
}