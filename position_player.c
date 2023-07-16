/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:07:08 by hel-hadd          #+#    #+#             */
/*   Updated: 2023/07/16 07:56:10 by mmeziani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north(t_tazi_data *data, int i, int j)
{
	data->p.a = 270 * (M_PI / 180.0);
	data->p.x = j * BLOCK_SIZE + BLOCK_SIZE / 2;
	data->p.y = i * BLOCK_SIZE + BLOCK_SIZE / 2;
	return ;
}

void	west(t_tazi_data *data, int i, int j)
{
	data->p.a = 180 * (M_PI / 180.0);
	data->p.x = j * BLOCK_SIZE + BLOCK_SIZE / 2;
	data->p.y = i * BLOCK_SIZE + BLOCK_SIZE / 2;
	return ;
}

void	east(t_tazi_data *data, int i, int j)
{
	data->p.a = 0 * (M_PI / 180.0);
	data->p.x = j * BLOCK_SIZE + BLOCK_SIZE / 2;
	data->p.y = i * BLOCK_SIZE + BLOCK_SIZE / 2;
	return ;
}

void	south(t_tazi_data *data, int i, int j)
{
	data->p.a = 90 * (M_PI / 180.0);
	data->p.x = j * BLOCK_SIZE + BLOCK_SIZE / 2;
	data->p.y = i * BLOCK_SIZE + BLOCK_SIZE / 2;
	return ;
}

void	position_player(t_tazi_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N')
				north(data, i, j);
			else if (data->map[i][j] == 'W')
				west(data, i, j);
			else if (data->map[i][j] == 'E')
				east(data, i, j);
			else if (data->map[i][j] == 'S')
				south(data, i, j);
			j++;
		}
		i++;
	}
}
