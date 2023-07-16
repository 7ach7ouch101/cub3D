/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_norm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 05:56:35 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/07/16 07:46:35 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	for_norm(double angl, t_tazi_data *data, double *x_s, t_ray *ray_h)
{
	if (angl > M_PI_2 && angl < M_PI_2 * 3)
	{
		*x_s = -BLOCK_SIZE;
		ray_h->x = floor(data->p.x / BLOCK_SIZE) * (BLOCK_SIZE) - 0.0001;
	}
	else
	{
		*x_s = BLOCK_SIZE;
		ray_h->x = floor(data->p.x / BLOCK_SIZE) * (BLOCK_SIZE) + BLOCK_SIZE;
	}
}

void	for_norm2(double angl, t_tazi_data *data, double *y_s, t_ray *ray_h)
{
	if (angl > 0 && angl < M_PI)
	{
		*y_s = BLOCK_SIZE;
		ray_h->y = floor(data->p.y / BLOCK_SIZE) * (BLOCK_SIZE) + BLOCK_SIZE;
	}
	else
	{
		*y_s = -BLOCK_SIZE;
		ray_h->y = floor(data->p.y / (BLOCK_SIZE)) * (BLOCK_SIZE) - 0.0001;
	}
}
