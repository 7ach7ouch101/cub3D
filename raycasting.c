/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-hadd <hel-hadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:30:11 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/07/15 06:47:54 by hel-hadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void vertical_ray(t_tazi_data *data, t_ray *ray_h, double angl)// |
{
    double x_s;
    double y_s;
    
    ray_h->dist = HUGE_VALF;
    ray_h->a = angl;
    if(angl > M_PI_2 && angl < M_PI_2 * 3)
    {
        x_s = -BLOCK_SIZE;
        ray_h->x = floor(data->p.x / BLOCK_SIZE) * (BLOCK_SIZE) - 0.0001;
    }
    else
    {
        x_s = BLOCK_SIZE;
        ray_h->x = floor(data->p.x /BLOCK_SIZE) * (BLOCK_SIZE) + BLOCK_SIZE;
    }
    ray_h->y = data->p.y + (ray_h->x - data->p.x) * tan(angl);
    y_s = x_s * tan(angl);
    while(ray_h->x/BLOCK_SIZE < data->map_len_max && ray_h->y/BLOCK_SIZE < data->map_wei_max && ray_h->x >= 0 && ray_h->y >= 0)
    {
        if (data->map[(int) ray_h->y/BLOCK_SIZE][(int)ray_h->x/BLOCK_SIZE] == '1')
        {   
            ray_h->dist = sqrt(pow(ray_h->y - data->p.y , 2) + pow(ray_h->x - data->p.x, 2));
            return;
        }
        ray_h->y += y_s;
        ray_h->x += x_s;
    }
}
void horizontal_ray(t_tazi_data *data, t_ray *ray_h, double angl)
{
    double x_s;
    double y_s;
    
    ray_h->dist = HUGE_VALF;
    ray_h->a = angl;
    if(angl > 0 && angl < M_PI)
    {
        y_s = BLOCK_SIZE;
        ray_h->y = floor(data->p.y /BLOCK_SIZE) * (BLOCK_SIZE) + BLOCK_SIZE;
    }
    else
    {
        y_s = -BLOCK_SIZE;
        ray_h->y = floor(data->p.y / (BLOCK_SIZE)) * (BLOCK_SIZE) - 0.0001 ;
    }
    ray_h->x = data->p.x + (ray_h->y - data->p.y) / tan(angl);
    x_s = y_s / tan(angl);  
    while(ray_h->x/BLOCK_SIZE < data->map_len_max && ray_h->y/BLOCK_SIZE < data->map_wei_max && ray_h->x >= 0 && ray_h->y >= 0)
    {
        if (data->map[(int) ray_h->y/BLOCK_SIZE][(int)ray_h->x/BLOCK_SIZE] == '1')
        {
            ray_h->dist = sqrt(pow(ray_h->y - data->p.y , 2) + pow(ray_h->x - data->p.x, 2));
            return;
        }
        ray_h->y += y_s;
        ray_h->x += x_s;
    }
}

t_ray ray_info(t_tazi_data *data, int i)
{
    double angl;
    t_ray ray_h;
    t_ray ray_v;
   double c;
    
    angl = data->p.a - (FOV / 2) + (FOV * i / WN_WIDTH);
 
    angl = remainder(angl, 2 * M_PI);

    if(angl < 0)
        angl = (2 * M_PI) + angl;

    
    horizontal_ray(data, &ray_h, angl);
    vertical_ray(data, &ray_v, angl);
    if (ray_h.dist <= ray_v.dist)
    {

        c = cos(angl - data->p.a);

        ray_h.bol = 1;
        ray_h.dist = ray_h.dist * c;

        return(ray_h);
    }

    else
    {
        c = cos(angl - data->p.a);
        ray_h.bol = 0;
        ray_v.dist = ray_v.dist * c;
        return(ray_v);
    }
}

void cast_ray(t_tazi_data *data)
{
    int i;

    i = 0;
    while (i < WN_WIDTH)
    {
        data->ray[i] = ray_info(data, i);
        i++;
    }
    return;
}